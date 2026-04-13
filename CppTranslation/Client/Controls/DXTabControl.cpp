#include "DXTabControl.h"
#include "DXLabel.h"
#include "CEnvir.h"

namespace Client::Controls
{
    // DXTabControl Implementation

    DXTab* DXTabControl::GetSelectedTab() const
    {
        return _SelectedTab;
    }

    void DXTabControl::SetSelectedTab(DXTab* value)
    {
        if (_SelectedTab == value)
            return;

        DXTab* oldValue = _SelectedTab;
        _SelectedTab = value;

        OnSelectedTabChanged(oldValue, value);
    }

    int DXTabControl::GetMarginLeft() const
    {
        return _MarginLeft;
    }

    void DXTabControl::SetMarginLeft(int value)
    {
        if (_MarginLeft == value)
            return;

        int oldValue = _MarginLeft;
        _MarginLeft = value;

        OnMarginLeftChanged(oldValue, value);
    }

    int DXTabControl::GetPadding() const
    {
        return _Padding;
    }

    void DXTabControl::SetPadding(int value)
    {
        if (_Padding == value)
            return;

        int oldValue = _Padding;
        _Padding = value;

        OnPaddingChanged(oldValue, value);
    }

    void DXTabControl::OnSelectedTabChanged(DXTab* oValue, DXTab* nValue)
    {
        SelectedTabChanged.Invoke(this, EventArgs::Empty);

        if (oValue != nullptr && oValue->Parent == this)
            oValue->SetSelected(false);

        if (nValue != nullptr)
            nValue->SetSelected(true);
    }

    void DXTabControl::OnMarginLeftChanged(int oValue, int nValue)
    {
        MarginLeftChanged.Invoke(this, EventArgs::Empty);
        TabsChanged();
    }

    void DXTabControl::OnPaddingChanged(int oValue, int nValue)
    {
        PaddingChanged.Invoke(this, EventArgs::Empty);
        TabsChanged();
    }

    void DXTabControl::OnDisplayAreaChanged(const Rectangle& oValue, const Rectangle& nValue)
    {
        DXControl::OnDisplayAreaChanged(oValue, nValue);

        if (Parent == nullptr)
            return;

        for (DXControl* control : Controls)
        {
            DXTab* tab = dynamic_cast<DXTab*>(control);

            if (tab == nullptr || tab->Updating)
                continue;

            control->SetSize(Size(Parent->GetSize().Width - control->GetLocation().X, Parent->GetSize().Height - control->GetLocation().Y));
        }
        TabsChanged();
    }

    DXTabControl::DXTabControl()
    {
        PassThrough = true;
    }

    void DXTabControl::SetNewTab()
    {
        if (IsDisposed)
            return;

        for (DXControl* control : Controls)
        {
            DXTab* tab = dynamic_cast<DXTab*>(control);

            if (tab == nullptr || tab == _SelectedTab)
                continue;

            _SelectedTab = nullptr;
            SetSelectedTab(tab);
            return;
        }

        _SelectedTab = nullptr;
    }

    void DXTabControl::TabsChanged()
    {
        if (_SelectedTab == nullptr)
        {
            for (DXControl* control : Controls)
            {
                DXTab* tab = dynamic_cast<DXTab*>(control);

                if (tab == nullptr || tab == _SelectedTab)
                    continue;

                SetSelectedTab(tab);
                break;
            }
        }

        int x = _MarginLeft;
        int width = 0;
        
        for (DXButton* control : TabButtons)
        {
            if (!control->GetVisible())
                continue;

            if (control->RightAligned)
            {
                width = control->GetSize().Width + _Padding;
                continue;
            }

            control->SetLocation(Point(x, 0));
            x += control->GetSize().Width + _Padding;
        }

        for (DXButton* control : TabButtons)
        {
            if (!control->GetVisible())
                continue;

            if (!control->RightAligned)
                continue;

            control->SetLocation(Point(GetSize().Width - width, 0));
            width -= control->GetSize().Width + 1;
        }
    }

    void DXTabControl::Dispose(bool disposing)
    {
        DXControl::Dispose(disposing);

        if (disposing)
        {
            _SelectedTab = nullptr;
            SelectedTabChanged.Clear();

            TabButtons.clear();
            
            _Padding = 0;
            _MarginLeft = 0;

            PaddingChanged.Clear();
            MarginLeftChanged.Clear();
        }
    }

    // DXTab Implementation

    DXTabControl* DXTab::GetCurrentTabControl() const
    {
        return _CurrentTabControl;
    }

    void DXTab::SetCurrentTabControl(DXTabControl* value)
    {
        if (_CurrentTabControl == value)
            return;

        DXTabControl* oldValue = _CurrentTabControl;
        _CurrentTabControl = value;

        OnCurrentTabControlChanged(oldValue, value);
    }

    bool DXTab::GetDrawOtherBorder() const
    {
        return _DrawOtherBorder;
    }

    void DXTab::SetDrawOtherBorder(bool value)
    {
        if (_DrawOtherBorder == value)
            return;

        bool oldValue = _DrawOtherBorder;
        _DrawOtherBorder = value;

        OnDrawOtherBorderChanged(oldValue, value);
    }

    bool DXTab::GetSelected() const
    {
        return _Selected;
    }

    void DXTab::SetSelected(bool value)
    {
        if (_Selected == value)
            return;

        bool oldValue = _Selected;
        _Selected = value;

        OnSelectedChanged(oldValue, value);
    }

    int DXTab::GetMinimumTabWidth() const
    {
        return _MinimumTabWidth;
    }

    void DXTab::SetMinimumTabWidth(int value)
    {
        if (_MinimumTabWidth == value)
            return;

        int oldValue = _MinimumTabWidth;
        _MinimumTabWidth = value;

        OnMinimumTabWidthChanged(oldValue, value);
    }

    void DXTab::OnCurrentTabControlChanged(DXTabControl* oValue, DXTabControl* nValue)
    {
        if (oValue != nullptr && oValue->GetSelectedTab() == this)
        {
            oValue->SetSelectedTab(nullptr);
            oValue->SetNewTab();
        }

        if (oValue != nullptr && nValue != nullptr)
            TabButton->MovePoint = Point(TabButton->MovePoint.X - oValue->GetDisplayArea().X + nValue->GetDisplayArea().X, 
                                          TabButton->MovePoint.Y - oValue->GetDisplayArea().Y + nValue->GetDisplayArea().Y);

        if (oValue != nullptr && oValue->Controls.empty())
            oValue->Dispose();

        CurrentTabControlChanged.Invoke(this, EventArgs::Empty);
    }

    void DXTab::OnDrawOtherBorderChanged(bool oValue, bool nValue)
    {
        DrawOtherBorderChanged.Invoke(this, EventArgs::Empty);
    }

    void DXTab::OnSelectedChanged(bool oValue, bool nValue)
    {
        if (_Selected)
        {
            SetVisible(true);
            TabButton->Pressed = true;

            if (TabButton->LibraryFile != LibraryFile::None)
            {
                // Empty in C#
            }
            else
            {
                TabButton->ButtonType = ButtonType::DeselectedTab;
                TabButton->Label->SetForeColour(Color::White);
            }
        }
        else
        {
            SetVisible(false);
            TabButton->Pressed = false;

            if (TabButton->LibraryFile != LibraryFile::None)
            {
                // Empty in C#
            }
            else
            {
                TabButton->ButtonType = ButtonType::DeselectedTab;
                TabButton->Label->SetForeColour(Color(198, 166, 99));
            }
        }

        SelectedChanged.Invoke(this, EventArgs::Empty);
    }

    void DXTab::OnMinimumTabWidthChanged(int oValue, int nValue)
    {
        MinimumTabWidthChanged.Invoke(this, EventArgs::Empty);

        if (TabButton != nullptr)
        {
            Size labelSize = DXLabel::GetSize(TabButton->Label->GetText(), TabButton->Label->GetFont(), TabButton->Label->Outline);
            TabButton->SetSize(Size(std::max(_MinimumTabWidth, labelSize.Width), DXControl::TabHeight));
        }
    }

    void DXTab::OnDisplayAreaChanged(const Rectangle& oValue, const Rectangle& nValue)
    {
        DXControl::OnDisplayAreaChanged(oValue, nValue);

        if (Parent == nullptr)
            return;

        if (IsResizing && Updating)
            return;

        SetSize(Size(Parent->GetSize().Width - GetLocation().X, Parent->GetSize().Height - GetLocation().Y));
    }

    void DXTab::OnParentChanged(DXControl* oValue, DXControl* nValue)
    {
        DXControl::OnParentChanged(oValue, nValue);

        DXTabControl* oldTab = dynamic_cast<DXTabControl*>(oValue);

        if (oldTab != nullptr)
        {
            auto it = std::find(oldTab->TabButtons.begin(), oldTab->TabButtons.end(), TabButton);
            if (it != oldTab->TabButtons.end())
                oldTab->TabButtons.erase(it);
            oldTab->TabsChanged();
        }

        if (Parent == nullptr)
            TabButton->Parent = nullptr;

        if (Parent == nullptr)
            return;

        SetSize(Size(Parent->GetSize().Width - GetLocation().X, Parent->GetSize().Height - GetLocation().Y));

        DXTabControl* tab = dynamic_cast<DXTabControl*>(Parent);

        if (tab == nullptr)
            return;
        
        SetSelected(tab->GetSelectedTab() == this);
        TabButton->Parent = tab;
        
        auto it = std::find(tab->Controls.begin(), tab->Controls.end(), TabButton);
        if (it != tab->Controls.end())
            tab->Controls.erase(it);
        
        tab->Controls.insert(tab->Controls.begin(), TabButton);
        tab->TabButtons.push_back(TabButton);
        tab->TabsChanged();

        SetCurrentTabControl(tab);
    }

    void DXTab::OnSizeChanged(const Size& oValue, const Size& nValue)
    {
        if (IsResizing)
        {
            if (Updating)
                return;
            
            Point location = Parent->GetLocation();
            Size size = Size(Parent->GetSize().Width - oValue.Width + nValue.Width, 
                            Parent->GetSize().Height - oValue.Height + nValue.Height);

            if (ResizeUp)
                location = Point(location.X, location.Y + oValue.Height - nValue.Height);

            if (ResizeLeft)
                location = Point(location.X + oValue.Width - nValue.Width, location.Y);

            Updating = true;
            Parent->SetSize(size);
            Parent->SetLocation(location);
            SetLocation(Point(0, DXControl::TabHeight - 1));
            Updating = false;
            return;
        }

        DXControl::OnSizeChanged(oValue, nValue);
    }

    DXTab::DXTab()
    {
        SetLocation(Point(0, DXControl::TabHeight - 1));
        BackColour = Color(16, 8, 8);
        DrawTexture = true;
        BorderColour = Color(198, 166, 99);
        PassThrough = true;
        SetVisible(false);

        _MinimumTabWidth = 60;

        TabButton = new DXButton();
        TabButton->ButtonType = ButtonType::DeselectedTab;
        TabButton->SetSize(Size(60, DXControl::TabHeight));
        
        TabButton->Label->TextChanged += [this](void* sender, EventArgs* e)
        {
            Size labelSize = DXLabel::GetSize(TabButton->Label->GetText(), TabButton->Label->GetFont(), TabButton->Label->Outline);
            TabButton->SetSize(Size(std::max(_MinimumTabWidth, labelSize.Width), DXControl::TabHeight));
        };
        
        TabButton->MouseClick += [this](void* sender, MouseEventArgs* e)
        {
            DXTabControl* tab = dynamic_cast<DXTabControl*>(TabButton->Parent);
            if (tab == nullptr)
                return;
            tab->SetSelectedTab(this);
        };
        
        TabButton->LocationChanged += [this](void* sender, EventArgs* e)
        {
            TabButton_LocationChanged(sender, e);
        };
        
        TabButton->IsMovingChanged += [this](void* sender, EventArgs* e)
        {
            TabButton_IsMovingChanged(sender, e);
        };
        
        OldOpacity = nullptr;
    }

    void DXTab::TabButton_IsMovingChanged(void* sender, EventArgs* e)
    {
        if (!IsMoving)
        {
            DXTabControl* cTab = dynamic_cast<DXTabControl*>(Parent);
            if (cTab != nullptr)
            {
                auto it = std::find(cTab->Controls.begin(), cTab->Controls.end(), TabButton);
                if (it != cTab->Controls.end())
                    cTab->Controls.erase(it);
                cTab->Controls.insert(cTab->Controls.begin(), TabButton);
                cTab->TabsChanged();
            }
            else
            {
                DXControl* oldParent = Parent;

                DXTabControl* nTab = new DXTabControl();
                nTab->Parent = TabButton->Parent->Parent;
                nTab->SetLocation(Point(TabButton->DisplayArea.X - ActiveScene->GetLocation().X, TabButton->DisplayArea.Y - ActiveScene->GetLocation().Y));
                nTab->SetVisible(true);
                nTab->PassThrough = TabButton->Parent->PassThrough;
                nTab->SetSize(TabButton->Parent->GetSize());
                nTab->Movable = TabButton->Parent->Movable;
                nTab->Border = TabButton->Parent->Border;
                nTab->BorderColour = TabButton->Parent->BorderColour;
                nTab->AllowResize = TabButton->Parent->AllowResize;

                Parent = nTab;
                nTab->SetSelectedTab(this);
                oldParent->Dispose();
            }

            TabButton->Tag = nullptr;
            SetSize(Size(Parent->GetSize().Width - GetLocation().X, Parent->GetSize().Height - GetLocation().Y));
        }
    }

    void DXTab::TabButton_LocationChanged(void* sender, EventArgs* e)
    {
        if (Updating || !TabButton->IsMoving)
            return;

        if (Parent->Parent == nullptr)
            return;

        const int threshold = 20;
        
        for (DXControl* control : Parent->Parent->Controls)
        {
            DXTabControl* tab = dynamic_cast<DXTabControl*>(control);

            if (tab == nullptr)
                continue;
            
            if (tab->GetDisplayArea().Left - TabButton->GetDisplayArea().Right > threshold ||
                tab->GetDisplayArea().Top - TabButton->GetDisplayArea().Bottom > threshold ||
                TabButton->GetDisplayArea().Left - tab->GetDisplayArea().Right > threshold ||
                TabButton->GetDisplayArea().Top - tab->GetDisplayArea().Top > threshold)
                continue;

            DXControl* oldParent = Parent;
            Updating = true;
            Parent = control;
            Updating = false;

            if (dynamic_cast<DXTabControl*>(oldParent) == nullptr)
                oldParent->Dispose();

            SetVisible(tab == Parent);
            Parent = tab;

            if (OldOpacity != nullptr)
                SetOpacity(*OldOpacity);

            TabButton->Tag = nullptr;

            int w = 0;
            int pivot = TabButton->GetLocation().X + TabButton->GetSize().Width / 2;
            
            for (size_t i = 0; i < tab->TabButtons.size(); i++)
            {
                DXButton* button = tab->TabButtons[i];

                w += button->GetSize().Width;

                if (w < pivot)
                    continue;

                if (tab->TabButtons[i] == TabButton)
                    return;

                auto it = std::find(tab->TabButtons.begin(), tab->TabButtons.end(), TabButton);
                if (it != tab->TabButtons.end())
                    tab->TabButtons.erase(it);
                
                tab->TabButtons.insert(tab->TabButtons.begin() + i, TabButton);
                
                Updating = true;
                tab->TabsChanged();
                Updating = false;
                break;
            }

            return;
        }

        if (dynamic_cast<DXTabControl*>(Parent) == nullptr)
        {
            Parent->SetLocation(Point(TabButton->DisplayArea.X - ActiveScene->GetLocation().X, 
                                       TabButton->DisplayArea.Y - ActiveScene->GetLocation().Y));
            return;
        }

        DXLabel* panel = new DXLabel();
        panel->SetVisible(true);
        panel->Parent = Parent->Parent;
        panel->SetSize(Parent->GetSize());
        panel->SetLocation(Point(TabButton->DisplayArea.X - ActiveScene->GetLocation().X, 
                                  TabButton->DisplayArea.Y - ActiveScene->GetLocation().Y));

        TabButton->Tag = new Size(Parent->GetSize());
        Parent = panel;
        SetVisible(true);

        OldOpacity = new float(GetOpacity());
        SetOpacity(0.5f);
    }

    void DXTab::UpdateBorderInformation()
    {
        BorderInformation = nullptr;
        
        if (!Border || GetSize().Width == 0 || GetSize().Height == 0)
            return;

        BorderInformation = new std::vector<Vector2>{
            Vector2(1, 1),
            Vector2(GetSize().Width - 1, 1),
            Vector2(GetSize().Width - 1, GetSize().Height - 1),
            Vector2(1, GetSize().Height - 1),
            Vector2(1, 1)
        };
    }

    void DXTab::Draw()
    {
        if (!IsVisible || GetSize().Width == 0 || GetSize().Height == 0)
            return;

        OnBeforeDraw();
        DrawControl();
        OnBeforeChildrenDraw();
        
        if (_DrawOtherBorder)
            DrawTabBorder();
        
        DrawChildControls();
        DrawBorder();
        OnAfterDraw();
    }

    void DXTab::DrawTabBorder()
    {
        if (InterfaceLibrary == nullptr)
            return;

        Surface* oldSurface = DXManager::CurrentSurface;
        DXManager::SetSurface(DXManager::ScratchSurface);
        DXManager::Device->Clear(ClearFlags::Target, 0, 0, 0);

        DrawEdges();

        DXManager::SetSurface(oldSurface);

        float oldOpacity = DXManager::Opacity;

        DXManager::SetOpacity(GetOpacity());

        PresentTexture(DXManager::ScratchTexture, Parent, DisplayArea, ForeColour, this);

        DXManager::SetOpacity(oldOpacity);
    }

    void DXTab::DrawEdges()
    {
        InterfaceLibrary->Draw(25, 0, 0, Color::White, false, 1.0f, ImageType::Image);

        Size s = InterfaceLibrary->GetSize(26);
        InterfaceLibrary->Draw(26, GetSize().Width - s.Width, 0, Color::White, false, 1.0f, ImageType::Image);

        s = InterfaceLibrary->GetSize(8);
        InterfaceLibrary->Draw(8, 0, GetSize().Height - s.Height, Color::White, false, 1.0f, ImageType::Image);

        s = InterfaceLibrary->GetSize(9);
        InterfaceLibrary->Draw(9, GetSize().Width - s.Width, GetSize().Height - s.Height, Color::White, false, 1.0f, ImageType::Image);

        int x = s.Width;
        int y = s.Height;

        s = InterfaceLibrary->GetSize(2);
        InterfaceLibrary->Draw(2, x, 0, Color::White, Rectangle(0, 0, GetSize().Width - x * 2, s.Height), 1.0f, ImageType::Image);
        InterfaceLibrary->Draw(2, x, GetSize().Height - s.Height, Color::White, Rectangle(0, 0, GetSize().Width - x * 2, s.Height), 1.0f, ImageType::Image);

        s = InterfaceLibrary->GetSize(1);
        InterfaceLibrary->Draw(1, 0, y, Color::White, Rectangle(0, 0, s.Width, GetSize().Height - y * 2), 1.0f, ImageType::Image);
        InterfaceLibrary->Draw(1, GetSize().Width - s.Width, y, Color::White, Rectangle(0, 0, s.Width, GetSize().Height - y * 2), 1.0f, ImageType::Image);
    }

    void DXTab::Dispose(bool disposing)
    {
        DXTabControl* tab = dynamic_cast<DXTabControl*>(Parent);
        if (tab != nullptr)
            tab->SetNewTab();

        DXControl::Dispose(disposing);

        if (disposing)
        {
            if (TabButton != nullptr)
            {
                if (!TabButton->IsDisposed)
                    TabButton->Dispose();

                TabButton = nullptr;
            }

            if (OldOpacity != nullptr)
            {
                delete OldOpacity;
                OldOpacity = nullptr;
            }
            
            _DrawOtherBorder = false;
            Updating = false;

            _CurrentTabControl = nullptr;
            _Selected = false;

            SelectedChanged.Clear();
            DrawOtherBorderChanged.Clear();
            CurrentTabControlChanged.Clear();
        }
    }
}
