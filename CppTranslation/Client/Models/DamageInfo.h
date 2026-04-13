#pragma once

#include "../Envir/CEnvir.h"
#include "MirLibrary.h"
#include <DateTime.h>

namespace Client::Models
{
    public ref class DamageInfo
    {
    public:
        // Properties
        property int Value
        {
            int get() { return _Value; }
            void set(int value)
            {
                if (_Value == value) return;
                int oldValue = _Value;
                _Value = value;
                OnValueChanged(oldValue, value);
            }
        }

        property bool Block
        {
            bool get() { return _Block; }
            void set(bool value)
            {
                if (_Block == value) return;
                bool oldValue = _Block;
                _Block = value;
                OnBlockChanged(oldValue, value);
            }
        }

        property bool Miss
        {
            bool get() { return _Miss; }
            void set(bool value)
            {
                if (_Miss == value) return;
                bool oldValue = _Miss;
                _Miss = value;
                OnMissChanged(oldValue, value);
            }
        }

        property bool Critical
        {
            bool get() { return _Critical; }
            void set(bool value)
            {
                if (_Critical == value) return;
                bool oldValue = _Critical;
                _Critical = value;
                OnCriticalChanged(oldValue, value);
            }
        }

        // Events
        event EventHandler<EventArgs^>^ ValueChanged;
        event EventHandler<EventArgs^>^ BlockChanged;
        event EventHandler<EventArgs^>^ MissChanged;
        event EventHandler<EventArgs^>^ CriticalChanged;

        // Static field
        static MirLibrary^ Library;

        // Properties (auto-implemented)
        property DateTime StartTime { DateTime get(); void set(DateTime value); }
        property TimeSpan AppearDelay { TimeSpan get(); void set(TimeSpan value); }
        property TimeSpan ShowDelay { TimeSpan get(); void set(TimeSpan value); }
        property TimeSpan HideDelay { TimeSpan get(); void set(TimeSpan value); }

        // Fields
        int BlueWidth, RedWidth, GreenWidth, OrangeWidth, WhiteWidth;
        int BlueIndex, RedIndex, GreenIndex, OrangeIndex, WhiteIndex;
        int DrawHeight;
        property int DrawY { int get(); void set(int value); }
        bool Visible;
        float Opacity;

        // Constructor and static constructor
        DamageInfo();
        static DamageInfo();

        // Methods
        int Bottom();
        void Process(DamageInfo^ previous);
        void Draw(int drawX, int drawY);

    protected:
        virtual void OnValueChanged(int oValue, int nValue);
        virtual void OnBlockChanged(bool oValue, bool nValue);
        virtual void OnMissChanged(bool oValue, bool nValue);
        virtual void OnCriticalChanged(bool oValue, bool nValue);

    private:
        int _Value;
        bool _Block;
        bool _Miss;
        bool _Critical;

        DateTime _StartTime;
        TimeSpan _AppearDelay;
        TimeSpan _ShowDelay;
        TimeSpan _HideDelay;
        int _DrawY;
    };
}
