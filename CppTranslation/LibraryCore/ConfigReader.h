#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <numeric>

namespace Library
{

    public static class ConfigReader
    {
        private static readonly Regex HeaderRegex = new Regex(@"^\[(?<Header>.+)\]$", RegexOptions.Compiled);
        private static readonly Regex EntryRegex = new Regex(@"^(?<Key>.*?)=(?<Value>.*)$", RegexOptions.Compiled);
        private static readonly Regex ColorRegex = new Regex(@"\[A:\s?(?<A>[0-9]{1,3}),\s?R:\s?(?<R>[0-9]{1,3}),\s?G:\s?(?<G>[0-9]{1,3}),\s?B:\s?(?<B>[0-9]{1,3})\]", RegexOptions.Compiled);

        public static readonly std::unordered_map<Type, object> ConfigObjects = new std::unordered_map<Type, object>();

        private static readonly std::unordered_map<Type, Dictionary<std::string, Dictionary<std::string, std::string>>> ConfigContents = new std::unordered_map<Type, Dictionary<std::string, Dictionary<std::string, std::string>>>();
        
        public static void Load(Assembly assembly)
        {
            Type[] types = assembly.GetTypes();
            
            foreach (Type type in types)
            {
                ConfigPath config = type.GetCustomAttribute<ConfigPath>();

                if (config == null) continue;

                object ob = null;
                if (!type.IsAbstract || !type.IsSealed)
                    ConfigObjects[type] = ob = Activator.CreateInstance(type);

                if (!config.Disabled)
                    ReadConfig(type, AdjustPath(config.Path, assembly), ob);
};
};
        public static void Save(Assembly assembly)
        {
            Type[] types = assembly.GetTypes();

            foreach (Type type in types)
            {
                ConfigPath config = type.GetCustomAttribute<ConfigPath>();

                if (config == null) continue;

                object ob = null;

                if (!type.IsAbstract || !type.IsSealed)
                    ob = ConfigObjects[type];

                if (!config.Disabled)
                    SaveConfig(type, AdjustPath(config.Path, assembly), ob);
};
};

        public static std::string AdjustPath(std::string originalPath, Assembly assembly)
        {
            var subFolder = GetSubFolder(assembly);

            if (!std::string.IsNullOrEmpty(subFolder))
            {
                return Path.GetFullPath(Path.Combine(AppDomain.CurrentDomain.BaseDirectory, subFolder, $"{originalPath}"));
};

            return Path.GetFullPath(Path.Combine(AppDomain.CurrentDomain.BaseDirectory, $"{originalPath}"));
};

        private static std::string GetSubFolder(Assembly assembly)
        {
            std::string assemblyName = assembly.GetName().Name;

            if (assemblyName.StartsWith("Plugin.", StringComparison.OrdinalIgnoreCase))
            {
                return Globals.PluginPath(assemblyName);
};

            return null;
};

        private static void ReadConfig(Type type, std::string path, object ob)
        {
            if (!File.Exists(path)) return;

            PropertyInfo[] properties = type.GetProperties();

            std::unordered_map<std::string, Dictionary<std::string, std::string>> contents = ConfigContents[type] = new std::unordered_map<std::string, Dictionary<std::string, std::string>>();
            
            std::string[] lines = File.ReadAllLines(path);

            std::unordered_map<std::string, std::string> section = null;

            foreach (std::string line in lines)
            {
                Match match = HeaderRegex.Match(line);
                if (match.Success)
                {
                    section = new std::unordered_map<std::string, std::string>();
                    contents[match.Groups["Header"].Value] = section;
                    continue;
};

                if (section == null) continue;

                match = EntryRegex.Match(line);

                if (!match.Success) continue;

                section[match.Groups["Key"].Value] = UnescapeSpecialCharacters(match.Groups["Value"].Value);
};

            std::string lastSection = null;

            foreach (PropertyInfo property in properties)
            {
                ConfigSection config = property.GetCustomAttribute<ConfigSection>();

                if (config != null) lastSection = config.Section;

                if (lastSection == null) continue;

                ConfigPropertyIgnore ignore = property.GetCustomAttribute<ConfigPropertyIgnore>();

                if (ignore != null) continue;

                MethodInfo method = typeof(ConfigReader).GetMethod("Read", new[] { typeof(Type), typeof(std::string), typeof(std::string), property.PropertyType });

                property.SetValue(ob, method.Invoke(null, new[] { type, lastSection, property.Name, property.GetValue(ob) }));
};
};

        private static void SaveConfig(Type type, std::string path, object ob)
        {
            PropertyInfo[] properties = type.GetProperties();
            std::unordered_map<std::string, Dictionary<std::string, std::string>> contents = ConfigContents[type] = new std::unordered_map<std::string, Dictionary<std::string, std::string>>();

            std::string lastSection = null;

            foreach (PropertyInfo property in properties)
            {
                ConfigSection config = property.GetCustomAttribute<ConfigSection>();

                if (config != null) lastSection = config.Section;

                if (lastSection == null) continue;

                ConfigPropertyIgnore ignore = property.GetCustomAttribute<ConfigPropertyIgnore>();

                if (ignore != null) continue;

                MethodInfo method = typeof(ConfigReader).GetMethod("Write", new[] { typeof(Type), typeof(std::string), typeof(std::string), property.PropertyType });

                method.Invoke(ob, new[] { type, lastSection, property.Name, property.GetValue(ob) });
};

            std::vector<std::string> lines = new std::vector<std::string>();

            foreach (std::pair<std::string, std::unordered_map<std::string, std::string>> header in contents)
            {
                lines.Add($"[{header.Key}]");

                foreach (std::pair<std::string, std::string> entries in header.Value)
                {
                    std::string escapedValue = EscapeSpecialCharacters(entries.Value);

                    lines.Add($"{entries.Key}={escapedValue}");
};

                lines.Add(std::string.Empty);
};

            if (!Directory.Exists(Path.GetDirectoryName(path)))
                Directory.CreateDirectory(Path.GetDirectoryName(path));

            File.WriteAllLines(path, lines, Encoding.Unicode);
};

        private static std::string EscapeSpecialCharacters(std::string value)
        {
            if (std::string.IsNullOrEmpty(value)) return value;

            return value.Replace("\n", "\\n").Replace("\r", "\\r").Replace("\t", "\\t");
};
        private static std::string UnescapeSpecialCharacters(std::string value)
        {
            if (std::string.IsNullOrEmpty(value)) return value;

            return value.Replace("\\n", "\n").Replace("\\r", "\r").Replace("\\t", "\t");
};

        private static bool TryGetEntry(Type type, std::string section, std::string key, out std::string value)
        {
            value = null;
            std::unordered_map<std::string, Dictionary<std::string, std::string>> contents;
            std::unordered_map<std::string, std::string> entries;

            if (!ConfigContents.TryGetValue(type, out contents))
                ConfigContents[type] = contents = new std::unordered_map<std::string, Dictionary<std::string, std::string>>();
                
            if (contents.TryGetValue(section, out entries))
                return entries.TryGetValue(key, out value);

            entries = new std::unordered_map<std::string, std::string>();
            contents[section] = entries;

            return false;
};

        #region Reads
        public static Boolean Read(Type type,std::string section, std::string key, Boolean value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                Boolean result;

                if (Boolean.TryParse(entry, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString();

            return value;
};

        public static Byte Read(Type type, std::string section, std::string key, Byte value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                Byte result;

                if (Byte.TryParse(entry, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString();

            return value;
};
        public static Int16 Read(Type type, std::string section, std::string key, Int16 value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                Int16 result;

                if (Int16.TryParse(entry, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString();

            return value;
};
        public static Int32 Read(Type type, std::string section, std::string key, Int32 value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                Int32 result;

                if (Int32.TryParse(entry, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString();

            return value;
};
        public static Int64 Read(Type type, std::string section, std::string key, Int64 value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                Int64 result;

                if (Int64.TryParse(entry, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString();

            return value;
};

        public static SByte Read(Type type, std::string section, std::string key, SByte value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                SByte result;

                if (SByte.TryParse(entry, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString();

            return value;
};
        public static UInt16 Read(Type type, std::string section, std::string key, UInt16 value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                UInt16 result;

                if (UInt16.TryParse(entry, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString();

            return value;
};
        public static UInt32 Read(Type type, std::string section, std::string key, UInt32 value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                UInt32 result;

                if (UInt32.TryParse(entry, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString();

            return value;
};
        public static UInt64 Read(Type type, std::string section, std::string key, UInt64 value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                UInt64 result;

                if (UInt64.TryParse(entry, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString();

            return value;
};

        public static Single Read(Type type, std::string section, std::string key, Single value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                Single result;

                if (Single.TryParse(entry, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString(CultureInfo.InvariantCulture);

            return value;
};
        public static Double Read(Type type, std::string section, std::string key, Double value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                Double result;

                if (Double.TryParse(entry, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString(CultureInfo.InvariantCulture);

            return value;
};
        public static Decimal Read(Type type, std::string section, std::string key, Decimal value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                Decimal result;

                if (Decimal.TryParse(entry, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString(CultureInfo.InvariantCulture);

            return value;
};

        public static Char Read(Type type, std::string section, std::string key, Char value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                Char result;

                if (Char.TryParse(entry, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString();

            return value;
};
        public static String Read(Type type, std::string section, std::string key, String value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
                return entry;

            ConfigContents[type][section][key] = value;

            return value;
};
        
        public static Point Read(Type type, std::string section, std::string key, Point value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                std::string[] data = entry.Split(new[] { ',' }, StringSplitOptions.RemoveEmptyEntries);

                int32_t x, y;

                if (data.Length == 2 && int32_t.TryParse(data[0], out x) && int32_t.TryParse(data[1], out y))
                    return new Point(x, y);
};

            ConfigContents[type][section][key] = $"{value.X}, {value.Y}";

            return value;
};
        public static Size Read(Type type, std::string section, std::string key, Size value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                std::string[] data = entry.Split(new[] { ',' }, StringSplitOptions.RemoveEmptyEntries);

                int32_t width, height;

                if (data.Length == 2 && int32_t.TryParse(data[0], out width) && int32_t.TryParse(data[1], out height))
                    return new Size(width, height);
};

            ConfigContents[type][section][key] = $"{value.Width}, {value.Height}";

            return value;
};
        public static SizeF Read(Type type, std::string section, std::string key, SizeF value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                std::string[] data = entry.Split(new[] { ',' }, StringSplitOptions.RemoveEmptyEntries);

                float width, height;

                if (data.Length == 2 && float.TryParse(data[0], out width) && float.TryParse(data[1], out height))
                    return new SizeF(width, height);
};

            ConfigContents[type][section][key] = $"{value.Width}, {value.Height}";

            return value;
};

        public static TimeSpan Read(Type type, std::string section, std::string key, TimeSpan value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                TimeSpan result;

                if (TimeSpan.TryParse(entry, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString();

            return value;
};
        public static DateTime Read(Type type, std::string section, std::string key, DateTime value)
        {
            std::string entry;

            if (TryGetEntry(type, section, key, out entry))
            {
                DateTime result;

                if (DateTime.TryParse(entry, CultureInfo.InvariantCulture, DateTimeStyles.None, out result))
                    return result;
};

            ConfigContents[type][section][key] = value.ToString(CultureInfo.InvariantCulture);

            return value;
};

        public static Color Read(Type type, std::string section, std::string key, Color value)
        {
            std::string entry;


            if (TryGetEntry(type, section, key, out entry))
            {
                Match match = ColorRegex.Match(entry);
                if (match.Success)
                {
                    int32_t a = int32_t.Parse(match.Groups["A"].Value);
                    int32_t r = int32_t.Parse(match.Groups["R"].Value);
                    int32_t g = int32_t.Parse(match.Groups["G"].Value);
                    int32_t b = int32_t.Parse(match.Groups["B"].Value);
                    
                    return Color.FromArgb(
                        std::min(Byte.MaxValue, std::max(Byte.MinValue, a)), 
                        std::min(Byte.MaxValue, std::max(Byte.MinValue, r)),
                        std::min(Byte.MaxValue, std::max(Byte.MinValue, g)),
                        std::min(Byte.MaxValue, std::max(Byte.MinValue, b)));
};
};

            ConfigContents[type][section][key] = $"[A:{value.A}, R:{value.R}, G:{value.G}, B:{value.B}]";

            return value;
};
        #endregion

        #region Writes
        public static void Write(Type type, std::string section, std::string key, Boolean value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString();
};

        public static void Write(Type type, std::string section, std::string key, Byte value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString();
};
        public static void Write(Type type, std::string section, std::string key, Int16 value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString();
};
        public static void Write(Type type, std::string section, std::string key, Int32 value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString();
};
        public static void Write(Type type, std::string section, std::string key, Int64 value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString();
};

        public static void Write(Type type, std::string section, std::string key, SByte value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString();
};
        public static void Write(Type type, std::string section, std::string key, UInt16 value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString();
};
        public static void Write(Type type, std::string section, std::string key, UInt32 value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString();
};
        public static void Write(Type type, std::string section, std::string key, UInt64 value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString();
};

        public static void Write(Type type, std::string section, std::string key, Single value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString(CultureInfo.InvariantCulture);
};
        public static void Write(Type type, std::string section, std::string key, Double value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString(CultureInfo.InvariantCulture);
};
        public static void Write(Type type, std::string section, std::string key, Decimal value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString(CultureInfo.InvariantCulture);
};

        public static void Write(Type type, std::string section, std::string key, Char value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString();
};
        public static void Write(Type type, std::string section, std::string key, String value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value;
};

        public static void Write(Type type, std::string section, std::string key, Point value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = $"{value.X}, {value.Y}";
};
        public static void Write(Type type, std::string section, std::string key, Size value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = $"{value.Width}, {value.Height}";
};

        public static void Write(Type type, std::string section, std::string key, TimeSpan value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString();
};
        public static void Write(Type type, std::string section, std::string key, DateTime value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = value.ToString(CultureInfo.InvariantCulture);
};
        public static void Write(Type type, std::string section, std::string key, Color value)
        {
            if (!ConfigContents[type].ContainsKey(section)) ConfigContents[type][section] = new std::unordered_map<std::string, std::string>();

            ConfigContents[type][section][key] = $"[A:{value.A}, R:{value.R}, G:{value.G}, B:{value.B}]";
};
        #endregion
};

    [AttributeUsage(AttributeTargets.Class)]
    class ConfigPath : Attribute
    {
        std::string Path;
        bool Disabled; // Skip the local ini file

        public ConfigPath(std::string path): this(path, false) { }

        public ConfigPath(std::string path, bool disabled)
        {
            Path = path;
            Disabled = disabled;
};
};

    [AttributeUsage(AttributeTargets.Property)]
    class ConfigSection : Attribute
    {
        std::string Section;

        public ConfigSection(std::string section)
        {
            Section = section;
};
};

    [AttributeUsage(AttributeTargets.Property)]
    class ConfigPropertyIgnore : Attribute
    {
        public ConfigPropertyIgnore() { }
};


}
