#include "DXColourControl.h"

namespace Client::Controls
{
    // DXColourControl implementation
    
    DXColourControl::DXColourControl()
    {
        Window = nullptr;
        _AllowNoColour = false;
        
        SetDrawTexture(true);
        SetBorder(true);
        SetBorderColour(Color::FromArgb(198, 166, 99));
        SetSize(Size(40, 15));
        SetBackColour(Color::Black());

        MouseClick += [this](void* sender, MouseEventArgs e) { DXColourControl_MouseClick(sender, e); };
    }

    DXColourControl::~DXColourControl()
    {
        Dispose(true);
    }

    void DXColourControl::SetAllowNoColour(bool value)
    {
        if (_AllowNoColour == value) return;

        bool oldValue = _AllowNoColour;
        _AllowNoColour = value;

        OnAllowNoColourChanged(oldValue, value);
    }

    void DXColourControl::OnAllowNoColourChanged(bool oValue, bool nValue)
    {
        if (AllowNoColourChanged) AllowNoColourChanged->Invoke(this, EventArgs::Empty());

        if (Window != nullptr)
            Window->SetAllowNoColour(nValue);
    }

    void DXColourControl::DXColourControl_MouseClick(void* sender, MouseEventArgs e)
    {
        if (Window != nullptr)
        {
            if (!Window->GetIsDisposed())
                Window->Dispose();
            delete Window;
            Window = nullptr;
        }

        Window = new DXColourPicker();
        Window->SetTarget(this);
        // Window->SetParent(ActiveScene); // Requires ActiveScene global
        Window->SetPreviousColour(GetBackColour());
        Window->SetSelectedColour(GetBackColour());
        Window->SetAllowNoColour(GetAllowNoColour());
        // Window->SetLocation(Point((ActiveScene.Size.Width - Window.Size.Width) / 2, (ActiveScene.Size.Height - Window.Size.Height) / 2));
    }

    void DXColourControl::Dispose(bool disposing)
    {
        DXControl::Dispose(disposing);

        if (disposing)
        {
            if (Window != nullptr)
            {
                if (!Window->GetIsDisposed())
                    Window->Dispose();
                delete Window;
                Window = nullptr;
            }
        }
    }

    // DXColourPicker implementation
    
    DXColourPicker::DXColourPicker()
    {
        _SelectedColour = Color::Empty();
        _AllowNoColour = false;
        Updating = false;
        PreviousColour = Color::Empty();
        
        SelectButton = nullptr;
        CancelButton = nullptr;
        EmptyButton = nullptr;
        Target = nullptr;
        RedBox = nullptr;
        GreenBox = nullptr;
        BlueBox = nullptr;
        ColourScaleBox = nullptr;
        ColourBox = nullptr;
        NoColourLabel = nullptr;

        SetSize(Size(380, 253));
        // TitleLabel.Text = CEnvir.Language.CommonControlColourPickerTitle;
        SetModal(true);
        SetHasFooter(true);

        CancelButton = new DXButton();
        CancelButton->SetParent(this);
        // CancelButton.Label.Text = CEnvir.Language.CommonControlCancel;
        CancelButton->SetLocation(Point(GetSize().Width / 2 + 10, GetSize().Height - 43));
        CancelButton->SetSize(Size(80, GetDefaultHeight()));
        CancelButton->MouseClick += [this](void* sender, MouseEventArgs e) { CancelButton_MouseClick(sender, e); };
        // CloseButton.MouseClick += [this](void* sender, MouseEventArgs e) { CancelButton_MouseClick(sender, e); };

        SelectButton = new DXButton();
        SelectButton->SetParent(this);
        // SelectButton.Label.Text = CEnvir.Language.CommonControlSelect;
        SelectButton->SetLocation(Point((GetSize().Width) / 2 - 80 - 10, GetSize().Height - 43));
        SelectButton->SetSize(Size(80, GetDefaultHeight()));
        SelectButton->MouseClick += [this](void* sender, MouseEventArgs e) { Dispose(); };

        EmptyButton = new DXButton();
        EmptyButton->SetParent(this);
        // EmptyButton.Label.Text = CEnvir.Language.CommonControlColourPickerEmptyLabel;
        EmptyButton->SetLocation(Point((GetSize().Width) / 2 - 80 - 10, GetSize().Height - 43));
        EmptyButton->SetSize(Size(80, GetDefaultHeight()));
        EmptyButton->SetVisible(GetAllowNoColour());
        EmptyButton->SetLocation(Point(GetSize().Width - EmptyButton->GetSize().Width - 10, 115));
        EmptyButton->MouseClick += [this](void* sender, MouseEventArgs e) { EmptyButton_MouseClick(sender, e); };

        ColourScaleBox = new DXControl();
        ColourScaleBox->SetLocation(Point(20, 40));
        ColourScaleBox->SetParent(this);
        ColourScaleBox->SetBorder(true);
        ColourScaleBox->SetBorderColour(Color::FromArgb(198, 166, 99));
        ColourScaleBox->SetSize(Size(200, 149));
        ColourScaleBox->AfterDraw += [this](void* sender, EventArgs e) 
        {
            // PresentTexture(DXManager.ColourPallete, ColourScaleBox, ColourScaleBox.DisplayArea, Color.White, this);
        };
        ColourScaleBox->MouseClick += [this](void* sender, MouseEventArgs e) { ColourScaleBox_MouseClick(sender, e); };

        RedBox = new DXNumberBox();
        RedBox->SetChange(5);
        RedBox->SetMaxValue(255);
        RedBox->SetParent(this);
        RedBox->SetLocation(Point(GetSize().Width - RedBox->GetSize().Width - 10, 40));
        // RedBox.ValueTextBox.ValueChanged += [this](void* sender, EventArgs e) { ColourBox_ValueChanged(sender, e); };

        DXLabel* label = new DXLabel();
        label->SetParent(this);
        // label.Text = CEnvir.Language.CommonControlColourPickerRedLabel;
        // label.Location = new Point(RedBox.Location.X - label.Size.Width - 5, (RedBox.Size.Height - label.Size.Height) / 2 + RedBox.Location.Y);

        GreenBox = new DXNumberBox();
        GreenBox->SetChange(5);
        GreenBox->SetMaxValue(255);
        GreenBox->SetParent(this);
        GreenBox->SetLocation(Point(GetSize().Width - GreenBox->GetSize().Width - 10, 65));
        // GreenBox.ValueTextBox.ValueChanged += [this](void* sender, EventArgs e) { ColourBox_ValueChanged(sender, e); };

        label = new DXLabel();
        label->SetParent(this);
        // label.Text = CEnvir.Language.CommonControlColourPickerGreenLabel;
        // label.Location = new Point(GreenBox.Location.X - label.Size.Width - 5, (GreenBox.Size.Height - label.Size.Height) / 2 + GreenBox.Location.Y);

        BlueBox = new DXNumberBox();
        BlueBox->SetChange(5);
        BlueBox->SetMaxValue(255);
        BlueBox->SetParent(this);
        BlueBox->SetLocation(Point(GetSize().Width - BlueBox->GetSize().Width - 10, 90));
        // BlueBox.ValueTextBox.ValueChanged += [this](void* sender, EventArgs e) { ColourBox_ValueChanged(sender, e); };

        label = new DXLabel();
        label->SetParent(this);
        // label.Text = CEnvir.Language.CommonControlColourPickerBlueLabel;
        // label.Location = new Point(BlueBox.Location.X - label.Size.Width - 5, (BlueBox.Size.Height - label.Size.Height) / 2 + BlueBox.Location.Y);

        ColourBox = new DXControl();
        ColourBox->SetSize(BlueBox->GetValueTextBox()->GetSize());
        ColourBox->SetLocation(Point(BlueBox->GetLocation().X + BlueBox->GetValueTextBox()->GetLocation().X, 172));
        ColourBox->SetBackColour(GetSelectedColour());
        ColourBox->SetBorder(true);
        ColourBox->SetDrawTexture(true);
        ColourBox->SetBorderColour(Color::FromArgb(198, 166, 99));
        ColourBox->SetParent(this);
        ColourBox->SetVisible(GetSelectedColour() != Color::Empty());
        label = new DXLabel();
        label->SetParent(this);
        // label.Text = CEnvir.Language.CommonControlColourPickerColourLabel;
        // label.Location = new Point(BlueBox.Location.X - label.Size.Width - 5, (ColourBox.Size.Height - label.Size.Height) / 2 + ColourBox.Location.Y);

        NoColourLabel = new DXLabel();
        NoColourLabel->SetParent(this);
        NoColourLabel->SetLocation(Point(BlueBox->GetLocation().X + BlueBox->GetValueTextBox()->GetLocation().X, 172));
        // NoColourLabel.Text = CEnvir.Language.CommonControlColourPickerNoneLabel;
        NoColourLabel->SetVisible(GetSelectedColour() == Color::Empty());
    }

    DXColourPicker::~DXColourPicker()
    {
        Dispose(true);
    }

    void DXColourPicker::SetSelectedColour(Color value)
    {
        if (_SelectedColour == value) return;

        Color oldValue = _SelectedColour;
        _SelectedColour = value;

        OnSelectedColourChanged(oldValue, value);
    }

    void DXColourPicker::OnSelectedColourChanged(Color oValue, Color nValue)
    {
        if (SelectedColourChanged) SelectedColourChanged->Invoke(this, EventArgs::Empty());

        if (ColourBox != nullptr)
            ColourBox->SetBackColour(GetSelectedColour());

        if (GetSelectedColour() == Color::FromArgb(0, 0, 0, 0))
        {
            ColourBox->SetVisible(false);
            NoColourLabel->SetVisible(true);
        }
        else
        {
            ColourBox->SetVisible(true);
            NoColourLabel->SetVisible(false);
        }

        if (Target != nullptr)
            Target->SetBackColour(GetSelectedColour());

        Updating = true;
        if (RedBox != nullptr) RedBox->SetValue(GetSelectedColour().R);
        if (GreenBox != nullptr) GreenBox->SetValue(GetSelectedColour().G);
        if (BlueBox != nullptr) BlueBox->SetValue(GetSelectedColour().B);
        Updating = false;
    }

    void DXColourPicker::SetAllowNoColour(bool value)
    {
        if (_AllowNoColour == value) return;

        bool oldValue = _AllowNoColour;
        _AllowNoColour = value;

        OnAllowNoColourChanged(oldValue, value);
    }

    void DXColourPicker::OnAllowNoColourChanged(bool oValue, bool nValue)
    {
        if (AllowNoColourChanged) AllowNoColourChanged->Invoke(this, EventArgs::Empty());

        if (EmptyButton != nullptr)
            EmptyButton->SetVisible(nValue);
    }

    void DXColourPicker::ColourScaleBox_MouseClick(void* sender, MouseEventArgs e)
    {
        int x = e.X - ColourScaleBox->GetDisplayArea().X;
        int y = e.Y - ColourScaleBox->GetDisplayArea().Y;

        if (x < 0 || y < 0 || x >= 200 || y >= 149) return;

        // SelectedColour = Color.FromArgb(DXManager.PalleteData[(y * 200 + x) * 4 + 2], DXManager.PalleteData[(y * 200 + x) * 4 + 1], DXManager.PalleteData[(y * 200 + x) * 4]);
    }

    void DXColourPicker::CancelButton_MouseClick(void* sender, MouseEventArgs e)
    {
        if (Target != nullptr)
            Target->SetBackColour(PreviousColour);
        Dispose();
    }

    void DXColourPicker::ColourBox_ValueChanged(void* sender, EventArgs e)
    {
        if (Updating) return;

        if (RedBox && GreenBox && BlueBox)
            SetSelectedColour(Color::FromArgb(static_cast<int>(RedBox->GetValue()), static_cast<int>(GreenBox->GetValue()), static_cast<int>(BlueBox->GetValue())));
    }

    void DXColourPicker::EmptyButton_MouseClick(void* sender, MouseEventArgs e)
    {
        if (Updating) return;

        SetSelectedColour(Color::FromArgb(0, 0, 0, 0));
    }

    void DXColourPicker::Dispose(bool disposing)
    {
        DXWindow::Dispose(disposing);

        if (disposing)
        {
            Updating = false;
            _SelectedColour = Color::Empty();
            SelectedColourChanged.reset();
            PreviousColour = Color::Empty();

            if (SelectButton != nullptr)
            {
                if (!SelectButton->GetIsDisposed())
                    SelectButton->Dispose();
                delete SelectButton;
                SelectButton = nullptr;
            }

            if (CancelButton != nullptr)
            {
                if (!CancelButton->GetIsDisposed())
                    CancelButton->Dispose();
                delete CancelButton;
                CancelButton = nullptr;
            }

            if (EmptyButton != nullptr)
            {
                if (!EmptyButton->GetIsDisposed())
                    EmptyButton->Dispose();
                delete EmptyButton;
                EmptyButton = nullptr;
            }

            Target = nullptr;

            if (RedBox != nullptr)
            {
                if (!RedBox->GetIsDisposed())
                    RedBox->Dispose();
                delete RedBox;
                RedBox = nullptr;
            }

            if (GreenBox != nullptr)
            {
                if (!GreenBox->GetIsDisposed())
                    GreenBox->Dispose();
                delete GreenBox;
                GreenBox = nullptr;
            }

            if (BlueBox != nullptr)
            {
                if (!BlueBox->GetIsDisposed())
                    BlueBox->Dispose();
                delete BlueBox;
                BlueBox = nullptr;
            }

            if (ColourScaleBox != nullptr)
            {
                if (!ColourScaleBox->GetIsDisposed())
                    ColourScaleBox->Dispose();
                delete ColourScaleBox;
                ColourScaleBox = nullptr;
            }

            if (ColourBox != nullptr)
            {
                if (!ColourBox->GetIsDisposed())
                    ColourBox->Dispose();
                delete ColourBox;
                ColourBox = nullptr;
            }

            if (NoColourLabel != nullptr)
            {
                if (!NoColourLabel->GetIsDisposed())
                    NoColourLabel->Dispose();
                delete NoColourLabel;
                NoColourLabel = nullptr;
            }
        }
    }
}
