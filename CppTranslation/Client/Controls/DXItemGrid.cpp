#include "DXItemGrid.h"
#include "DXManager.h"
#include <SlimDX/Direct3D9.h>

using namespace System;
using namespace System::Drawing;
using namespace SlimDX;
using namespace Client::Controls;

DXItemGrid::DXItemGrid()
{
    DrawTexture = true;
    BackColour = Color::FromArgb(24, 12, 12);
    Border = true;
    BorderColour = Color::FromArgb(99, 83, 50);
    Size = System::Drawing::Size(DXItemCell::CellWidth, DXItemCell::CellHeight);

    AllowLink = true;
    VisibleHeight = 1000;
}

void DXItemGrid::OnGridTypeChanged(GridType oValue, GridType nValue)
{
    for each (DXItemCell^ cell in Grid)
        cell->GridType = GridType;

    GridTypeChanged?.Invoke(this, EventArgs::Empty);
}

void DXItemGrid::OnGridSizeChanged(Size oValue, Size nValue)
{
    Size = System::Drawing::Size(GridSize.Width * (DXItemCell::CellWidth - 1 + (GridPadding * 2)) + 1, 
                                  Math::Min(GridSize.Height, VisibleHeight) * (DXItemCell::CellHeight - 1 + (GridPadding * 2)) + 1);
    CreateGrid();

    GridSizeChanged?.Invoke(this, EventArgs::Empty);
}

void DXItemGrid::OnGridPaddingChanged(int oValue, int nValue)
{
    Size = System::Drawing::Size(GridSize.Width * (DXItemCell::CellWidth - 1 + (GridPadding * 2)) + 1, 
                                  Math::Min(GridSize.Height, VisibleHeight) * (DXItemCell::CellHeight - 1 + (GridPadding * 2)) + 1);
    CreateGrid();

    GridPaddingChanged?.Invoke(this, EventArgs::Empty);
}

void DXItemGrid::OnItemGridChanged(array<ClientUserItem^>^ oValue, array<ClientUserItem^>^ nValue)
{
    ItemGridChanged?.Invoke(this, EventArgs::Empty);

    for each (DXItemCell^ cell in Grid)
        cell->ItemGrid = ItemGrid;
}

void DXItemGrid::OnLinkedChanged(bool oValue, bool nValue)
{
    for each (DXItemCell^ cell in Grid)
        cell->Linked = Linked;

    LinkedChanged?.Invoke(this, EventArgs::Empty);
}

void DXItemGrid::OnAllowLinkChanged(bool oValue, bool nValue)
{
    if (Grid == nullptr) return;

    for each (DXItemCell^ cell in Grid)
        cell->AllowLink = AllowLink;

    AllowLinkChanged?.Invoke(this, EventArgs::Empty);
}

void DXItemGrid::OnReadOnlyChanged(bool oValue, bool nValue)
{
    if (Grid == nullptr) return;

    for each (DXItemCell^ cell in Grid)
        cell->ReadOnly = ReadOnly;

    ReadOnlyChanged?.Invoke(this, EventArgs::Empty);
}

void DXItemGrid::OnScrollValueChanged(int oValue, int nValue)
{
    UpdateGridDisplay();
    ScrollValueChanged?.Invoke(this, EventArgs::Empty);
}

void DXItemGrid::OnVisibleHeightChanged(int oValue, int nValue)
{
    Size = System::Drawing::Size(GridSize.Width * (DXItemCell::CellWidth - 1) + 1, 
                                  Math::Min(GridSize.Height, VisibleHeight) * (DXItemCell::CellHeight - 1) + 1);

    UpdateGridDisplay();
    VisibleHeightChanged?.Invoke(this, EventArgs::Empty);
}

void DXItemGrid::OnOpacityChanged(float oValue, float nValue)
{
    DXControl::OnOpacityChanged(oValue, nValue);

    if (Grid == nullptr) return;

    for each (DXItemCell^ cell in Grid)
        cell->Opacity = Opacity;
}

void DXItemGrid::CreateGrid()
{
    if (Grid != nullptr)
    {
        for each (DXItemCell^ cell in Grid)
            cell->Dispose();
    }

    Grid = gcnew array<DXItemCell^>(GridSize.Width * GridSize.Height);

    for (int y = 0; y < GridSize.Height; y++)
    {
        for (int x = 0; x < GridSize.Width; x++)
        {
            int index = y * GridSize.Width + x;
            Grid[index] = gcnew DXItemCell();
            Grid[index]->Parent = this;
            Grid[index]->Location = Point((x * (DXItemCell::CellWidth - 1 + (GridPadding * 2))) + GridPadding, 
                                           (y * (DXItemCell::CellHeight - 1 + (GridPadding * 2))) + GridPadding);
            Grid[index]->Slot = y * GridSize.Width + x;
            Grid[index]->HostGrid = this;
            Grid[index]->ItemGrid = ItemGrid;
            Grid[index]->GridType = GridType;
            Grid[index]->Linked = Linked;
            Grid[index]->AllowLink = AllowLink;
            Grid[index]->ReadOnly = ReadOnly;
        }
    }

    UpdateGridDisplay();
}

void DXItemGrid::UpdateGridDisplay()
{
    for (int y = 0; y < GridSize.Height; y++)
    {
        for (int x = 0; x < GridSize.Width; x++)
        {
            DXItemCell^ cell = Grid[y * GridSize.Width + x];

            if (y < ScrollValue || y >= ScrollValue + VisibleHeight)
            {
                cell->Visible = false;
                continue;
            }

            cell->Visible = true;
            cell->Location = Point((x * (DXItemCell::CellWidth - 1 + (GridPadding * 2))) + GridPadding, 
                                    ((y - ScrollValue) * (DXItemCell::CellHeight - 1 + (GridPadding * 2))) + GridPadding);
        }
    }
}

void DXItemGrid::OnClearTexture()
{
    DXControl::OnClearTexture();

    if (!Border || BorderInformation == nullptr) return;

    DXManager::Line->Draw(BorderInformation, BorderColour);

    for (int i = 0; i <= GridSize.Width; i++)
    {
        array<Vector2>^ line = gcnew array<Vector2> {
            Vector2(((DXItemCell::CellWidth - 1 + (GridPadding * 2)) * i), 0),
            Vector2(((DXItemCell::CellWidth - 1 + (GridPadding * 2)) * i), Size.Height)
        };
        DXManager::Line->Draw(line, BorderColour);
    }

    for (int i = 0; i <= Math::Min(GridSize.Height, VisibleHeight); i++)
    {
        array<Vector2>^ line = gcnew array<Vector2> {
            Vector2(0, ((DXItemCell::CellHeight - 1 + (GridPadding * 2)) * i)),
            Vector2(Size.Width, ((DXItemCell::CellHeight - 1 + (GridPadding * 2)) * i))
        };
        DXManager::Line->Draw(line, BorderColour);
    }
}

void DXItemGrid::UpdateBorderInformation()
{
    BorderInformation = nullptr;
    if (!Border || Size.Width == 0 || Size.Height == 0) return;

    System::Collections::Generic::List<Vector2>^ border = gcnew System::Collections::Generic::List<Vector2>();
    border->Add(Vector2(0, 0));
    border->Add(Vector2(Size.Width - 1, 0));
    border->Add(Vector2(Size.Width - 1, Size.Height - 1));
    border->Add(Vector2(0, Size.Height - 1));
    border->Add(Vector2(0, 0));

    BorderInformation = border->ToArray();
}

void DXItemGrid::DrawBorder()
{
    // Empty - drawing handled in OnClearTexture
}

void DXItemGrid::ClearLinks()
{
    if (Grid != nullptr)
    {
        for each (DXItemCell^ cell in Grid)
        {
            if (cell->Link == nullptr) continue;
            if (cell->Link->GridType == GridType::TradeUser) continue;
            cell->Link = nullptr;
        }
    }
}

DXItemGrid::~DXItemGrid()
{
    Dispose(true);
    DXControl::~DXControl();
}

void DXItemGrid::Dispose(bool disposing)
{
    if (disposing)
    {
        _GridType = GridType::None;
        _GridSize = System::Drawing::Size::Empty;
        _ItemGrid = nullptr;
        _Linked = false;
        _AllowLink = false;
        _ReadOnly = false;
        _ScrollValue = 0;
        _VisibleHeight = 0;

        GridTypeChanged = nullptr;
        GridSizeChanged = nullptr;
        ItemGridChanged = nullptr;
        LinkedChanged = nullptr;
        AllowLinkChanged = nullptr;
        ReadOnlyChanged = nullptr;
        ScrollValueChanged = nullptr;
        VisibleHeightChanged = nullptr;

        if (Grid != nullptr)
        {
            for (int i = 0; i < Grid->Length; i++)
            {
                if (Grid[i] == nullptr) continue;
                if (!Grid[i]->IsDisposed)
                    Grid[i]->Dispose();
                Grid[i] = nullptr;
            }
        }

        Grid = nullptr;
    }
}
