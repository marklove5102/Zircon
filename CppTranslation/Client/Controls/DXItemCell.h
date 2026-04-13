#pragma once

#include "DXControl.h"
#include "DXLabel.h"
#include "../Library/Enum.h"
#include <vector>

namespace Client::Controls
{
    // Forward declarations
    class DXItemGrid;
    struct ClientUserItem;
    struct ItemInfo;

    class DXItemCell : public DXControl
    {
    public:
        // Static properties
        static DXItemCell* GetSelectedCell();
        static void SetSelectedCell(DXItemCell* value);
        
        static const int CellWidth = 36;
        static const int CellHeight = 36;

        // Properties
        bool GetFixedBorder() const { return _FixedBorder; }
        void SetFixedBorder(bool value);
        
        bool GetFixedBorderColour() const { return _FixedBorderColour; }
        void SetFixedBorderColour(bool value);
        
        GridType GetGridType() const { return _GridType; }
        void SetGridType(GridType value);
        
        DXItemGrid* GetHostGrid() const { return _HostGrid; }
        void SetHostGrid(DXItemGrid* value);
        
        ClientUserItem* GetItem() const;
        void SetItem(ClientUserItem* value);
        
        std::vector<ClientUserItem*>& GetItemGrid() { return _ItemGrid; }
        void SetItemGrid(std::vector<ClientUserItem*>& value);
        
        bool GetLocked() const { return _Locked; }
        void SetLocked(bool value);
        
        bool GetReadOnly() const { return _ReadOnly; }
        void SetReadOnly(bool value);
        
        bool GetSelected() const { return _Selected; }
        void SetSelected(bool value);
        
        int GetSlot() const { return _Slot; }
        void SetSlot(int value);
        
        bool GetShowCountLabel() const { return _ShowCountLabel; }
        void SetShowCountLabel(bool value);
        
        ClientUserItem* GetQuickInfoItem() const { return QuickInfoItem; }
        
        ItemInfo* GetQuickInfo() const { return _QuickInfo; }
        void SetQuickInfo(ItemInfo* value);
        
        ClientUserItem* GetQuickItem() const { return _QuickItem; }
        void SetQuickItem(ClientUserItem* value);
        
        DXItemCell* GetLink() const { return _Link; }
        void SetLink(DXItemCell* value);
        
        int64_t GetLinkedCount() const { return _LinkedCount; }
        void SetLinkedCount(int64_t value);
        
        bool GetLinked() const { return _Linked; }
        void SetLinked(bool value);
        
        bool GetAllowLink() const { return _AllowLink; }
        void SetAllowLink(bool value);
        
        bool GetHidden() const { return _Hidden; }
        void SetHidden(bool value);

        // Child controls
        DXLabel* CountLabel;

        // Events
        EventHandler<void>* FixedBorderChanged;
        EventHandler<void>* FixedBorderColourChanged;
        EventHandler<void>* GridTypeChanged;
        EventHandler<void>* HostGridChanged;
        EventHandler<void>* ItemChanged;
        EventHandler<void>* ItemGridChanged;
        EventHandler<void>* LockedChanged;
        EventHandler<void>* ReadOnlyChanged;
        EventHandler<void>* SelectedChanged;
        EventHandler<void>* SlotChanged;
        EventHandler<void>* ShowCountLabelChanged;
        EventHandler<void>* LinkedInfoChanged;
        EventHandler<void>* LinkedItemChanged;
        EventHandler<void>* LinkChanged;
        EventHandler<void>* LinkedCountChanged;
        EventHandler<void>* LinkedChanged;
        EventHandler<void>* AllowLinkChanged;
        EventHandler<void>* HiddenChanged;

        // Constructor
        DXItemCell();
        
        // Methods
        void RefreshItem();
        void HandleMouseWheel(void* e);
        void UpdateBorder();

        // Override methods
        void OnMouseWheel(void* e) override;
        void OnIsVisibleChanged(bool oValue, bool nValue) override;
        void OnBorderChanged(bool oValue, bool nValue) override;
        void OnBorderColourChanged(Color oValue, Color nValue) override;
        void OnEnabledChanged(bool oValue, bool nValue) override;

    protected:
        void OnClearTexture() override;
        void UpdateBorderInformation() override;
        void Dispose(bool disposing) override;

    private:
        // Backing fields
        bool _FixedBorder;
        bool _FixedBorderColour;
        GridType _GridType;
        DXItemGrid* _HostGrid;
        std::vector<ClientUserItem*> _ItemGrid;
        bool _Locked;
        bool _ReadOnly;
        bool _Selected;
        int _Slot;
        bool _ShowCountLabel;
        ItemInfo* _QuickInfo;
        ClientUserItem* _QuickItem;
        DXItemCell* _Link;
        int64_t _LinkedCount;
        bool _Linked;
        bool _AllowLink;
        bool _Hidden;
        
        ClientUserItem* QuickInfoItem;
        
        // Private methods
        void CountLabel_SizeChanged(void* sender, void* e);
        void OnFixedBorderChanged(bool oValue, bool nValue);
        void OnFixedBorderColourChanged(bool oValue, bool nValue);
        void OnGridTypeChanged(GridType oValue, GridType nValue);
        void OnHostGridChanged(DXItemGrid* oValue, DXItemGrid* nValue);
        void OnItemChanged(ClientUserItem* oValue, ClientUserItem* nValue);
        void OnItemGridChanged(std::vector<ClientUserItem*>& oValue, std::vector<ClientUserItem*>& nValue);
        void OnLockedChanged(bool oValue, bool nValue);
        void OnReadOnlyChanged(bool oValue, bool nValue);
        void OnSelectedChanged(bool oValue, bool nValue);
        void OnSlotChanged(int oValue, int nValue);
        void OnShowCountLabelChanged(bool oValue, bool nValue);
        void OnLinkedInfoChanged(ItemInfo* oValue, ItemInfo* nValue);
        void OnLinkedItemChanged(ClientUserItem* oValue, ClientUserItem* nValue);
        void OnLinkChanged(DXItemCell* oValue, DXItemCell* nValue);
        void OnLinkedCountChanged(int64_t oValue, int64_t nValue);
        void OnLinkedChanged(bool oValue, bool nValue);
        void OnAllowLinkChanged(bool oValue, bool nValue);
        void OnHiddenChanged(bool oValue, bool nValue);
    };

} // namespace Client::Controls
