#pragma once

#include "DXControl.h"
#include "DXItemCell.h"
#include "../Models/ClientUserItem.h"
#include <vector>

namespace Client::Controls
{
    public ref class DXItemGrid : DXControl
    {
    public:
        // Properties
        property GridType GridType
        {
            GridType get() { return _GridType; }
            void set(GridType value)
            {
                if (_GridType == value) return;
                GridType oldValue = _GridType;
                _GridType = value;
                OnGridTypeChanged(oldValue, value);
            }
        }

        property System::Drawing::Size GridSize
        {
            System::Drawing::Size get() { return _GridSize; }
            void set(System::Drawing::Size value)
            {
                if (_GridSize == value) return;
                System::Drawing::Size oldValue = _GridSize;
                _GridSize = value;
                OnGridSizeChanged(oldValue, value);
            }
        }

        property int GridPadding
        {
            int get() { return _GridPadding; }
            void set(int value)
            {
                if (_GridPadding == value) return;
                int oldValue = _GridPadding;
                _GridPadding = value;
                OnGridPaddingChanged(oldValue, value);
            }
        }

        property array<ClientUserItem^>^ ItemGrid
        {
            array<ClientUserItem^>^ get() { return _ItemGrid; }
            void set(array<ClientUserItem^>^ value)
            {
                if (_ItemGrid == value) return;
                array<ClientUserItem^>^ oldValue = _ItemGrid;
                _ItemGrid = value;
                OnItemGridChanged(oldValue, value);
            }
        }

        property bool Linked
        {
            bool get() { return _Linked; }
            void set(bool value)
            {
                if (_Linked == value) return;
                bool oldValue = _Linked;
                _Linked = value;
                OnLinkedChanged(oldValue, value);
            }
        }

        property bool AllowLink
        {
            bool get() { return _AllowLink; }
            void set(bool value)
            {
                if (_AllowLink == value) return;
                bool oldValue = _AllowLink;
                _AllowLink = value;
                OnAllowLinkChanged(oldValue, value);
            }
        }

        property bool ReadOnly
        {
            bool get() { return _ReadOnly; }
            void set(bool value)
            {
                if (_ReadOnly == value) return;
                bool oldValue = _ReadOnly;
                _ReadOnly = value;
                OnReadOnlyChanged(oldValue, value);
            }
        }

        property int ScrollValue
        {
            int get() { return _ScrollValue; }
            void set(int value)
            {
                if (_ScrollValue == value) return;
                int oldValue = _ScrollValue;
                _ScrollValue = value;
                OnScrollValueChanged(oldValue, value);
            }
        }

        property int VisibleHeight
        {
            int get() { return _VisibleHeight; }
            void set(int value)
            {
                if (_VisibleHeight == value) return;
                int oldValue = _VisibleHeight;
                _VisibleHeight = value;
                OnVisibleHeightChanged(oldValue, value);
            }
        }

        // Events
        event EventHandler<EventArgs^>^ GridTypeChanged;
        event EventHandler<EventArgs^>^ GridSizeChanged;
        event EventHandler<EventArgs^>^ GridPaddingChanged;
        event EventHandler<EventArgs^>^ ItemGridChanged;
        event EventHandler<EventArgs^>^ LinkedChanged;
        event EventHandler<EventArgs^>^ AllowLinkChanged;
        event EventHandler<EventArgs^>^ ReadOnlyChanged;
        event EventHandler<EventArgs^>^ ScrollValueChanged;
        event EventHandler<EventArgs^>^ VisibleHeightChanged;

        // Public fields
        array<DXItemCell^>^ Grid;

        // Constructor
        DXItemGrid();

        // Methods
        void CreateGrid();
        void UpdateGridDisplay();
        void ClearLinks();

    protected:
        virtual void OnGridTypeChanged(GridType oValue, GridType nValue);
        virtual void OnGridSizeChanged(System::Drawing::Size oValue, System::Drawing::Size nValue);
        virtual void OnGridPaddingChanged(int oValue, int nValue);
        virtual void OnItemGridChanged(array<ClientUserItem^>^ oValue, array<ClientUserItem^>^ nValue);
        virtual void OnLinkedChanged(bool oValue, bool nValue);
        virtual void OnAllowLinkChanged(bool oValue, bool nValue);
        virtual void OnReadOnlyChanged(bool oValue, bool nValue);
        virtual void OnScrollValueChanged(int oValue, int nValue);
        virtual void OnVisibleHeightChanged(int oValue, int nValue);
        virtual void OnOpacityChanged(float oValue, float nValue) override;
        virtual void OnClearTexture() override;
        virtual void UpdateBorderInformation() override;
        virtual void DrawBorder() override;
        virtual ~DXItemGrid() override;

    private:
        GridType _GridType;
        System::Drawing::Size _GridSize;
        int _GridPadding;
        array<ClientUserItem^>^ _ItemGrid;
        bool _Linked;
        bool _AllowLink;
        bool _ReadOnly;
        int _ScrollValue;
        int _VisibleHeight;

        void Dispose(bool disposing);
    };
}
