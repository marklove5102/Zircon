#pragma once

#include "DXControl.h"
#include <string>
#include <functional>

namespace Client::Controls
{
    class DXTextBox : public DXControl
    {
    public:
        // Static properties
        static DXTextBox* GetActiveTextBox();
        static void SetActiveTextBox(DXTextBox* value);

        // Properties
        bool GetEditable() const { return _Editable; }
        void SetEditable(bool value);

        // Font will be handled by system font
        void* GetFont() const { return _Font; }
        void SetFont(void* value);

        bool GetKeepFocus() const { return _KeepFocus; }
        void SetKeepFocus(bool value);

        int GetMaxLength() const { return _MaxLength; }
        void SetMaxLength(int value);

        bool GetPassword() const { return _Password; }
        void SetPassword(bool value);

        bool GetReadOnly() const { return _ReadOnly; }
        void SetReadOnly(bool value);

        // TextBox
        class MirTextBox* GetTextBox() const { return _TextBox; }

        // Events
        std::function<void()> EditableChanged;
        std::function<void()> FontChanged;
        std::function<void()> KeepFocusChanged;
        std::function<void()> MaxLengthChanged;
        std::function<void()> PasswordChanged;
        std::function<void()> ReadOnlyChanged;
        std::function<void()> TextBoxChanged;

        // Override events
        void OnBackColourChanged(const D2D1_COLOR_F& oValue, const D2D1_COLOR_F& nValue) override;
        void OnForeColourChanged(const D2D1_COLOR_F& oValue, const D2D1_COLOR_F& nValue) override;
        void OnDisplayAreaChanged(const RECT& oValue, const RECT& nValue) override;
        void OnSizeChanged(const SIZE& oValue, const SIZE& nValue) override;
        void OnIsVisibleChanged(bool oValue, bool nValue) override;
        void OnIsEnabledChanged(bool oValue, bool nValue) override;

        // Mouse state
        int Button; // MouseButtons
        long long ClickTime; // DateTime

        bool NeedFocus;

        // Constructor/Destructor
        DXTextBox();
        virtual ~DXTextBox();

        // Methods
        void OnActivated();
        void OnDeactivated();
        void OnMouseEnter() override;
        void OnMouseLeave() override;
        void UpdateDisplayArea() override;
        void OnMouseDown(int x, int y, int button, int clicks) override;
        void OnMouseMove(int x, int y, int clicks) override;
        void OnMouseUp(int x, int y, int button, int clicks) override;

        bool CanFocus();
        void SetFocus();
        void CheckFocus();

    protected:
        void CreateTexture() override;
        void DrawControl() override;
        void Dispose(bool disposing) override;

    private:
        static DXTextBox* _ActiveTextBox;

        bool _Editable = true;
        void* _Font = nullptr; // System font pointer
        bool _KeepFocus = false;
        int _MaxLength = 0;
        bool _Password = false;
        bool _ReadOnly = false;
        class MirTextBox* _TextBox = nullptr;

        // Event handlers
        void OnEditableChanged(bool oValue, bool nValue);
        void OnFontChanged(void* oValue, void* nValue);
        void OnKeepFocusChanged(bool oValue, bool nValue);
        void OnMaxLengthChanged(int oValue, int nValue);
        void OnPasswordChanged(bool oValue, bool nValue);
        void OnReadOnlyChanged(bool oValue, bool nValue);
        void OnTextBoxChanged(class MirTextBox* oValue, class MirTextBox* nValue);
    };

    // MirTextBox - Internal text box class
    class MirTextBox
    {
    public:
        DXTextBox* Owner;

        MirTextBox(DXTextBox* owner);
        ~MirTextBox();

        void NextTextBox();
        void PreviousTextBox();
        void SelectAll();
        void SetText(const std::wstring& text);
        std::wstring GetText() const;

        // Simulated events
        void OnMouseClick(int x, int y, int button, int clicks);
        void OnKeyDown(int keyCode, bool shift, bool alt, bool ctrl);
        void OnKeyUp(int keyCode, bool shift, bool alt, bool ctrl);
        void OnTextChanged();
        void OnSizeChanged(int width, int height);

    private:
        std::wstring _text;
        bool _selectedAll = false;
    };
}
