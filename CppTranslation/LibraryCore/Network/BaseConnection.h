#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Library::Network
{

    public abstract class BaseConnection
    {
        public static std::unordered_map<std::string, DiagnosticValue> Diagnostics = new std::unordered_map<std::string, DiagnosticValue>();
        public static std::unordered_map<Type, MethodInfo> PacketMethods = new std::unordered_map<Type, MethodInfo>();
        public static bool Monitor;

        bool Connected;
        protected bool Sending { get; set; }

        int32_t TotalBytesSent;
        int32_t TotalBytesReceived;
        int32_t TotalPacketsProcessed;

        public bool AdditionalLogging;

        protected TcpClient Client;

        DateTime TimeConnected;
        public TimeSpan Duration => Time.Now - TimeConnected;

        protected abstract TimeSpan TimeOutDelay { get; }
        DateTime TimeOutTime;

        private bool _disconnecting;
        public bool Disconnecting
        {
            get { return _disconnecting; }
            set
            {
                if (_disconnecting == value) return;
                _disconnecting = value;
                TimeOutTime = Time.Now.AddSeconds(2);
};
};

        public ConcurrentQueue<Packet> ReceiveList = new ConcurrentQueue<Packet>();
        public ConcurrentQueue<Packet> SendList = new ConcurrentQueue<Packet>();
        private uint8_t[] _rawData = new uint8_t[0];

        public EventHandler<Exception> OnException;

        protected BaseConnection(TcpClient client)
        {
            Client = client;
            Client.NoDelay = true;

            Connected = true;
            TimeConnected = Time.Now;

            TotalPacketsProcessed = 0;
};

        protected void BeginReceive()
        {
            try
            {
                if (Client == null || !Client.Connected) return;

                uint8_t[] rawBytes = new uint8_t[8 * 1024];

                Client.Client.BeginReceive(rawBytes, 0, rawBytes.Length, SocketFlags.None, ReceiveData, rawBytes);
};
            catch (Exception ex)
            {
                if (AdditionalLogging)
                    OnException(this, ex);
                Disconnecting = true;
};
};
        private void ReceiveData(IAsyncResult result)
        {
            try
            {
                if (!Connected) return;

                int32_t dataRead = Client.Client.EndReceive(result);

                if (dataRead == 0)
                {
                    Disconnecting = true;
                    return;
};

                TotalBytesReceived += dataRead;

                UpdateTimeOut();

                uint8_t[] rawBytes = result.AsyncState as uint8_t[];

                uint8_t[] temp = _rawData;
                _rawData = new uint8_t[dataRead + temp.Length];
                Buffer.BlockCopy(temp, 0, _rawData, 0, temp.Length);
                Buffer.BlockCopy(rawBytes, 0, _rawData, temp.Length, dataRead);

                Packet p;

                while ((p = Packet.ReceivePacket(_rawData, out _rawData)) != null)
                {
                    ReceiveList.Enqueue(p);
                    TotalPacketsProcessed++;
};

                BeginReceive();
};
            catch (Exception ex)
            {
                if (AdditionalLogging)
                    OnException(this, ex);
                Disconnecting = true;
};
};
        private void BeginSend(std::vector<uint8_t> data)
        {
            if (!Connected || data.Count == 0) return;

            try
            {
                Sending = true;
                TotalBytesSent += data.Count;
                Client.Client.BeginSend(data.ToArray(), 0, data.Count, SocketFlags.None, SendData, null);
                UpdateTimeOut();
};
            catch (Exception ex)
            {
                if (AdditionalLogging)
                    OnException(this, ex);
                Disconnecting = true;
                Sending = false;
};
};
        private void SendData(IAsyncResult result)
        {
            try
            {
                Sending = false;
                Client.Client.EndSend(result);
                UpdateTimeOut();
};
            catch (Exception ex)
            {
                if (AdditionalLogging)
                    OnException(this, ex);
                Disconnecting = true;
};
};
        public virtual void Enqueue(Packet p)
        {
            if (!Connected || p == null) return;

            SendList.Enqueue(p);
};

        public abstract void TryDisconnect();

        public virtual void Disconnect()
        {
            if (!Connected) return;

            Connected = false;

            SendList = null;
            ReceiveList = null;
            _rawData = null;

            Client.Client.Dispose();
            Client = null;
};

        public abstract void TrySendDisconnect(Packet p);

        public virtual void SendDisconnect(Packet p)
        {
            if (!Connected || Disconnecting)
            {
                Disconnecting = true;
                return;
};

            std::vector<uint8_t> data = new std::vector<uint8_t>();

            data.AddRange(p.GetPacketBytes());

            BeginSendDisconnect(data);
};
        private void BeginSendDisconnect(std::vector<uint8_t> data)
        {
            if (!Connected || data.Count == 0) return;

            if (Disconnecting) return;

            try
            {
                Disconnecting = true;

                TotalBytesSent += data.Count;
                Client.Client.BeginSend(data.ToArray(), 0, data.Count, SocketFlags.None, SendDataDisconnect, null);
};
            catch (Exception ex)
            {
                if (AdditionalLogging)
                    OnException(this, ex);
};
};
        private void SendDataDisconnect(IAsyncResult result)
        {

            try
            {
                Client.Client.EndSend(result);
};
            catch (Exception ex)
            {
                if (AdditionalLogging)
                    OnException(this, ex);
};
};

        public virtual void Process()
        {
            if (Client == null || !Client.Connected)
            {
                TryDisconnect();
                return;
};

            while (!ReceiveList.IsEmpty && !Disconnecting)
            {
                try
                {
                    Packet p;
                    if (!ReceiveList.TryDequeue(out p)) continue;

                    ProcessPacket(p);
};
                catch (NotImplementedException ex)
                {
                    OnException(this, ex);
                    Disconnecting = true;
};
                catch (Exception ex)
                {
                    OnException(this, ex);
                    throw;
};
};

            if (Time.Now >= TimeOutTime)
            {
                if (!Disconnecting)
                    TrySendDisconnect(new G.Disconnect { Reason = DisconnectReason.TimedOut });
                else
                    TryDisconnect();

                return;
};

            if (!Disconnecting && Sending)
                UpdateTimeOut();

            if (SendList.IsEmpty || Sending) return;

            std::vector<uint8_t> data = new std::vector<uint8_t>();
            while (!SendList.IsEmpty)
            {
                Packet p;

                if (!SendList.TryDequeue(out p)) continue;

                if (p == null) continue;

                try
                {
                    uint8_t[] bytes = p.GetPacketBytes();

                    data.AddRange(bytes);
};
                catch (Exception ex)
                {
                    OnException?.Invoke(this, ex);
                    Disconnecting = true;
                    return;
};


                if (!Monitor) continue;
                
                DiagnosticValue value;
                Type type = p.GetType();

                if (!Diagnostics.TryGetValue(type.FullName, out value))
                    Diagnostics[type.FullName] = value = new DiagnosticValue { Name = type.FullName };

                value.Count++;
                value.TotalSize += p.Length;
                
                if (p.Length > value.LargestSize)
                    value.LargestSize = p.Length;
};

            BeginSend(data);
};

        private void ProcessPacket(Packet p)
        {
            if (p == null) return;

            DateTime start = Time.Now;
            
            MethodInfo info;
            if (!PacketMethods.TryGetValue(p.PacketType, out info))
                PacketMethods[p.PacketType] = info = GetType().GetMethod("Process", new[] { p.PacketType });

            if (info == null)
                throw new NotImplementedException($"Not Implemented Exception: Method Process({p.PacketType}).");

            info.Invoke(this, new object[] { p });

            if (!Monitor) return;

            TimeSpan execution = Time.Now - start;
            DiagnosticValue value;

            if (!Diagnostics.TryGetValue(p.PacketType.FullName, out value))
                Diagnostics[p.PacketType.FullName] = value = new DiagnosticValue { Name = p.PacketType.FullName };

            value.Count++;
            value.TotalTime += execution;
            value.TotalSize += p.Length;

            if (execution > value.LargestTime)
                value.LargestTime = execution;

            if (p.Length > value.LargestSize)
                value.LargestSize = p.Length;
};

        public void UpdateTimeOut()
        {
            if (Disconnecting) return;

            TimeOutTime = Time.Now + TimeOutDelay;
};
};


    class DiagnosticValue
    {
        std::string Name;
        TimeSpan TotalTime;
        TimeSpan LargestTime;
        int32_t Count;
        int64_t TotalSize;
        int64_t LargestSize;

        public int64_t TotalTicks => TotalTime.Ticks;
        public int64_t TotalMilliseconds => TotalTicks / TimeSpan.TicksPerMillisecond;

        public int64_t LargestTicks => LargestTime.Ticks;
        public int64_t LargestMilliseconds => LargestTicks / TimeSpan.TicksPerMillisecond;
};

}
