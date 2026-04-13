#include "DXItemCell.h"
#include "DXItemGrid.h"
#include "../Envir/CEnvir.h"

namespace Client::Controls
{
    // Static members
    static DXItemCell* SelectedCellInstance = nullptr;
    
    DXItemCell* DXItemCell::GetSelectedCell()
    {
        return SelectedCellInstance;
    }
    
    void DXItemCell::SetSelectedCell(DXItemCell* value)
    {
        SelectedCellInstance = value;
    }

    DXItemCell::DXItemCell()
        : _FixedBorder(false),
          _FixedBorderColour(false),
          _GridType(GridType::None),
          _HostGrid(nullptr),
          _Locked(false),
          _ReadOnly(false),
          _Selected(false),
          _Slot(0),
          _ShowCountLabel(true),
          _QuickInfo(nullptr),
          _QuickItem(nullptr),
          _Link(nullptr),
          _LinkedCount(0),
          _Linked(false),
          _AllowLink(true),
          _Hidden(false),
          QuickInfoItem(nullptr),
          CountLabel(nullptr),
          FixedBorderChanged(nullptr),
          FixedBorderColourChanged(nullptr),
          GridTypeChanged(nullptr),
          HostGridChanged(nullptr),
          ItemChanged(nullptr),
          ItemGridChanged(nullptr),
          LockedChanged(nullptr),
          ReadOnlyChanged(nullptr),
          SelectedChanged(nullptr),
          SlotChanged(nullptr),
          ShowCountLabelChanged(nullptr),
          LinkedInfoChanged(nullptr),
          LinkedItemChanged(nullptr),
          LinkChanged(nullptr),
          LinkedCountChanged(nullptr),
          LinkedChanged(nullptr),
          AllowLinkChanged(nullptr),
          HiddenChanged(nullptr)
    {
        // BackColour = Color.Empty;
        SetBackColour(Color::Empty);
        
        // DrawTexture = true;
        SetDrawTexture(true);
        
        // BorderColour = Color.FromArgb(99, 83, 50);
        SetBorderColour(Color{ 99, 83, 50, 255 });
        
        // Size = new Size(CellWidth, CellHeight);
        SetSize(Size{ CellWidth, CellHeight });

        CountLabel = new DXLabel();
        CountLabel->SetForeColour(Color{ 255, 255, 0, 255 }); // Yellow
        // CountLabel->IsControl = false;
        CountLabel->SetParent(this);
        
        // CountLabel.SizeChanged += CountLabel_SizeChanged;
        // Note: Event handling needs implementation
    }

    void DXItemCell::CountLabel_SizeChanged(void* sender, void* e)
    {
        if (CountLabel != nullptr)
        {
            Size sz = GetSize();
            Size labelSize = CountLabel->GetSize();
            CountLabel->SetLocation(Point{ sz.Width - labelSize.Width, sz.Height - labelSize.Height });
        }
    }

    void DXItemCell::OnMouseWheel(void* e)
    {
        HandleMouseWheel(e);
    }

    void DXItemCell::HandleMouseWheel(void* e)
    {
        // Implementation depends on mouse wheel handling logic
        // This is a placeholder
    }

    void DXItemCell::OnIsVisibleChanged(bool oValue, bool nValue)
    {
        DXControl::OnIsVisibleChanged(oValue, nValue);

        if (_HostGrid == nullptr && !nValue)
            SetLink(nullptr);
    }

    void DXItemCell::OnBorderChanged(bool oValue, bool nValue)
    {
        DXControl::OnBorderChanged(oValue, nValue);
        
        // TextureValid = false;
        UpdateBorder();
    }

    void DXItemCell::OnBorderColourChanged(Color oValue, Color nValue)
    {
        DXControl::OnBorderColourChanged(oValue, nValue);
        
        // TextureValid = false;
        UpdateBorder();
    }

    void DXItemCell::OnEnabledChanged(bool oValue, bool nValue)
    {
        DXControl::OnEnabledChanged(oValue, nValue);
        
        UpdateBorder();
    }

    void DXItemCell::OnClearTexture()
    {
        DXControl::OnClearTexture();

        // if (!Border || BorderInformation == null) return;
        // DXManager.Line.Draw(BorderInformation, BorderColour);
        // Note: DXManager implementation needed
    }

    void DXItemCell::UpdateBorderInformation()
    {
        // BorderInformation = null;
        // if (!Border || Size.Width == 0 || Size.Height == 0) return;
        // Implementation depends on border rendering system
    }

    void DXItemCell::UpdateBorder()
    {
        // Implementation for updating border based on state
        // Checks Locked, Selected, Enabled, Hidden properties
    }

    void DXItemCell::RefreshItem()
    {
        // Implementation for refreshing the item display
        // Updates CountLabel, texture, etc.
    }

    // Property setters with event notifications
    void DXItemCell::SetFixedBorder(bool value)
    {
        if (_FixedBorder == value) return;
        bool oldValue = _FixedBorder;
        _FixedBorder = value;
        OnFixedBorderChanged(oldValue, value);
    }

    void DXItemCell::SetFixedBorderColour(bool value)
    {
        if (_FixedBorderColour == value) return;
        bool oldValue = _FixedBorderColour;
        _FixedBorderColour = value;
        OnFixedBorderColourChanged(oldValue, value);
    }

    void DXItemCell::SetGridType(GridType value)
    {
        if (_GridType == value) return;
        GridType oldValue = _GridType;
        _GridType = value;
        OnGridTypeChanged(oldValue, value);
    }

    void DXItemCell::SetHostGrid(DXItemGrid* value)
    {
        if (_HostGrid == value) return;
        DXItemGrid* oldValue = _HostGrid;
        _HostGrid = value;
        OnHostGridChanged(oldValue, value);
    }

    ClientUserItem* DXItemCell::GetItem() const
    {
        // Complex getter logic from C#
        if (_GridType == GridType::Belt || _GridType == GridType::AutoPotion)
        {
            if (QuickInfo != nullptr)
                return QuickInfoItem;
            return _QuickItem;
        }

        if (_Linked && _Link != nullptr)
            return _Link->GetItem();

        if (_Slot >= static_cast<int>(_ItemGrid.size()))
            return nullptr;

        return _ItemGrid[_Slot];
    }

    void DXItemCell::SetItem(ClientUserItem* value)
    {
        // Complex setter logic from C#
        ClientUserItem* currentItem = GetItem();
        if (currentItem == value || _Linked || _Slot >= static_cast<int>(_ItemGrid.size()))
            return;

        ClientUserItem* oldValue = currentItem;
        if (_Slot < static_cast<int>(_ItemGrid.size()))
            _ItemGrid[_Slot] = value;

        OnItemChanged(oldValue, value);
    }

    void DXItemCell::SetLocked(bool value)
    {
        if (_Locked == value) return;
        bool oldValue = _Locked;
        _Locked = value;
        OnLockedChanged(oldValue, value);
        UpdateBorder();
    }

    void DXItemCell::SetSelected(bool value)
    {
        if (_Selected == value) return;
        bool oldValue = _Selected;
        _Selected = value;
        OnSelectedChanged(oldValue, value);
        UpdateBorder();
    }

    void DXItemCell::SetSlot(int value)
    {
        if (_Slot == value) return;
        int oldValue = _Slot;
        _Slot = value;
        OnSlotChanged(oldValue, value);
        RefreshItem();
    }

    void DXItemCell::SetShowCountLabel(bool value)
    {
        if (_ShowCountLabel == value) return;
        bool oldValue = _ShowCountLabel;
        _ShowCountLabel = value;
        OnShowCountLabelChanged(oldValue, value);
    }

    void DXItemCell::SetQuickInfo(ItemInfo* value)
    {
        if (_QuickInfo == value) return;
        ItemInfo* oldValue = _QuickInfo;
        _QuickInfo = value;
        OnLinkedInfoChanged(oldValue, value);
    }

    void DXItemCell::SetQuickItem(ClientUserItem* value)
    {
        if (_QuickItem == value) return;
        ClientUserItem* oldValue = _QuickItem;
        _QuickItem = value;
        OnLinkedItemChanged(oldValue, value);
    }

    void DXItemCell::SetLink(DXItemCell* value)
    {
        if (_Link == value) return;
        DXItemCell* oldValue = _Link;
        _Link = value;
        OnLinkChanged(oldValue, value);
    }

    void DXItemCell::SetLinkedCount(int64_t value)
    {
        if (_LinkedCount == value) return;
        int64_t oldValue = _LinkedCount;
        _LinkedCount = value;
        OnLinkedCountChanged(oldValue, value);
    }

    void DXItemCell::SetLinked(bool value)
    {
        if (_Linked == value) return;
        bool oldValue = _Linked;
        _Linked = value;
        OnLinkedChanged(oldValue, value);
    }

    void DXItemCell::SetAllowLink(bool value)
    {
        if (_AllowLink == value) return;
        bool oldValue = _AllowLink;
        _AllowLink = value;
        OnAllowLinkChanged(oldValue, value);
    }

    void DXItemCell::SetHidden(bool value)
    {
        if (_Hidden == value) return;
        bool oldValue = _Hidden;
        _Hidden = value;
        OnHiddenChanged(oldValue, value);
        UpdateBorder();
    }

    // Event notification methods
    void DXItemCell::OnFixedBorderChanged(bool oValue, bool nValue)
    {
        if (FixedBorderChanged != nullptr)
            FixedBorderChanged->Invoke(this, nullptr);
    }

    void DXItemCell::OnFixedBorderColourChanged(bool oValue, bool nValue)
    {
        if (FixedBorderColourChanged != nullptr)
            FixedBorderColourChanged->Invoke(this, nullptr);
    }

    void DXItemCell::OnGridTypeChanged(GridType oValue, GridType nValue)
    {
        if (GridTypeChanged != nullptr)
            GridTypeChanged->Invoke(this, nullptr);
    }

    void DXItemCell::OnHostGridChanged(DXItemGrid* oValue, DXItemGrid* nValue)
    {
        if (HostGridChanged != nullptr)
            HostGridChanged->Invoke(this, nullptr);
    }

    void DXItemCell::OnItemChanged(ClientUserItem* oValue, ClientUserItem* nValue)
    {
        if (ItemChanged != nullptr)
            ItemChanged->Invoke(this, nullptr);
        RefreshItem();
    }

    void DXItemCell::OnItemGridChanged(std::vector<ClientUserItem*>& oValue, std::vector<ClientUserItem*>& nValue)
    {
        if (ItemGridChanged != nullptr)
            ItemGridChanged->Invoke(this, nullptr);
        if (ItemChanged != nullptr)
            ItemChanged->Invoke(this, nullptr);
        RefreshItem();
    }

    void DXItemCell::OnLockedChanged(bool oValue, bool nValue)
    {
        if (LockedChanged != nullptr)
            LockedChanged->Invoke(this, nullptr);
        UpdateBorder();
    }

    void DXItemCell::OnReadOnlyChanged(bool oValue, bool nValue)
    {
        if (ReadOnlyChanged != nullptr)
            ReadOnlyChanged->Invoke(this, nullptr);
    }

    void DXItemCell::OnSelectedChanged(bool oValue, bool nValue)
    {
        if (SelectedChanged != nullptr)
            SelectedChanged->Invoke(this, nullptr);
        UpdateBorder();
    }

    void DXItemCell::OnSlotChanged(int oValue, int nValue)
    {
        if (SlotChanged != nullptr)
            SlotChanged->Invoke(this, nullptr);
        if (ItemChanged != nullptr)
            ItemChanged->Invoke(this, nullptr);
        RefreshItem();
    }

    void DXItemCell::OnShowCountLabelChanged(bool oValue, bool nValue)
    {
        if (ShowCountLabelChanged != nullptr)
            ShowCountLabelChanged->Invoke(this, nullptr);
    }

    void DXItemCell::OnLinkedInfoChanged(ItemInfo* oValue, ItemInfo* nValue)
    {
        if (nValue != nullptr)
        {
            // QuickInfoItem = new ClientUserItem(nValue, 1);
            _QuickItem = nullptr;
            // Update belt link info index
        }
        else
        {
            QuickInfoItem = nullptr;
        }
        
        RefreshItem();
        
        if (LinkedInfoChanged != nullptr)
            LinkedInfoChanged->Invoke(this, nullptr);
    }

    void DXItemCell::OnLinkedItemChanged(ClientUserItem* oValue, ClientUserItem* nValue)
    {
        if (nValue != nullptr)
        {
            _QuickInfo = nullptr;
            // Update belt link item index
        }
        
        RefreshItem();
        
        if (LinkedItemChanged != nullptr)
            LinkedItemChanged->Invoke(this, nullptr);
    }

    void DXItemCell::OnLinkChanged(DXItemCell* oValue, DXItemCell* nValue)
    {
        if (oValue != nullptr && oValue->GetLink() == this)
            oValue->SetLink(nullptr);

        if (nValue != nullptr && nValue->GetLink() != this)
            nValue->SetLink(this);

        RefreshItem();
        UpdateBorder();

        if (LinkChanged != nullptr)
            LinkChanged->Invoke(this, nullptr);
    }

    void DXItemCell::OnLinkedCountChanged(int64_t oValue, int64_t nValue)
    {
        if (LinkedCountChanged != nullptr)
            LinkedCountChanged->Invoke(this, nullptr);
    }

    void DXItemCell::OnLinkedChanged(bool oValue, bool nValue)
    {
        if (LinkedChanged != nullptr)
            LinkedChanged->Invoke(this, nullptr);
    }

    void DXItemCell::OnAllowLinkChanged(bool oValue, bool nValue)
    {
        if (AllowLinkChanged != nullptr)
            AllowLinkChanged->Invoke(this, nullptr);
    }

    void DXItemCell::OnHiddenChanged(bool oValue, bool nValue)
    {
        if (HiddenChanged != nullptr)
            HiddenChanged->Invoke(this, nullptr);
        UpdateBorder();
    }

    void DXItemCell::Dispose(bool disposing)
    {
        DXControl::Dispose(disposing);

        if (disposing)
        {
            if (CountLabel != nullptr)
            {
                if (!CountLabel->GetIsDisposed())
                    CountLabel->Dispose();
                delete CountLabel;
                CountLabel = nullptr;
            }
            
            // Clear references
            QuickInfoItem = nullptr;
            _QuickInfo = nullptr;
            _QuickItem = nullptr;
            _Link = nullptr;
            _HostGrid = nullptr;
            _ItemGrid.clear();
        }
    }

} // namespace Client::Controls
