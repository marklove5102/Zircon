#include "DXItemAmountWindow.h"
#include "DXItemCell.h"
#include "DXScene.h"
#include "../Envir/CEnvir.h"
#include <algorithm>

namespace Client::Controls
{
    DXItemAmountWindow::DXItemAmountWindow(const std::string& caption, ClientUserItem* item)
        : ConfirmButton(nullptr), AmountBox(nullptr), ItemCell(nullptr), Amount(0)
    {
        SetHasFooter(true);

        // TitleLabel->Text = caption;
        if (TitleLabel != nullptr)
            TitleLabel->Text = caption;
        
        // SetClientSize(new Size(200, DXItemCell.CellHeight + 10));
        // Note: DXItemCell::CellHeight needs to be defined
        SetClientSize(Size{ 200, 40 + 10 }); // Placeholder

        // Parent = ActiveScene;
        if (ActiveScene != nullptr)
            SetParent(ActiveScene);
        
        // MessageBoxList.Add(this);
        // Modal = true;
        SetModal(true);

        // Center the window
        if (ActiveScene != nullptr)
        {
            RECT sceneArea = ActiveScene->GetDisplayArea();
            RECT displayArea = GetDisplayArea();
            int x = (sceneArea.right - sceneArea.left - (displayArea.right - displayArea.left)) / 2;
            int y = (sceneArea.bottom - sceneArea.top - (displayArea.bottom - displayArea.top)) / 2;
            SetLocation(Point{ x, y });
        }

        ConfirmButton = new DXButton();
        ConfirmButton->SetLocation(Point{ GetSize().Width / 2 + 10, GetSize().Height - 43 });
        ConfirmButton->SetSize(Size{ 80, 25 }); // DefaultHeight placeholder
        ConfirmButton->SetParent(this);
        if (ConfirmButton->Label != nullptr)
            ConfirmButton->Label->Text = "Confirm"; // CEnvir::Language.CommonControlConfirm
        // ConfirmButton.MouseClick += (o, e) => Dispose();

        AmountBox = new DXNumberBox();
        AmountBox->SetParent(this);
        if (item != nullptr)
        {
            AmountBox->SetMaxValue(static_cast<int>(item->Count));
            AmountBox->SetChange(std::max(int64_t(1), item->Count / 5));
        }

        // AmountBox.ValueTextBox.ValueChanged += (o, e) => { ... }
        // Note: Need to implement event handling
        
        ItemCell = new DXItemCell();
        // Calculate location
        RECT clientArea = GetClientArea();
        int cellWidth = 32; // DXItemCell::CellWidth placeholder
        int cellHeight = 32; // DXItemCell::CellHeight placeholder
        int amountBoxWidth = AmountBox->GetSize().Width;
        
        int x = clientArea.left + (clientArea.right - clientArea.left - cellWidth - amountBoxWidth - 5) / 2;
        int y = clientArea.top + 5;
        
        ItemCell->SetLocation(Point{ x, y });
        ItemCell->SetParent(this);
        ItemCell->SetFixedBorder(true);
        ItemCell->SetBorder(true);
        // ItemCell->ItemGrid = new[] { item };
        ItemCell->SetSlot(0);
        // ItemCell->GridType = GridType.None;
        ItemCell->SetReadOnly(true);

        // Position AmountBox next to ItemCell
        int amountBoxX = ItemCell->GetLocation().x + ItemCell->GetSize().Width + 10;
        int amountBoxY = ItemCell->GetLocation().y + (ItemCell->GetSize().Height - AmountBox->GetSize().Height) / 2;
        AmountBox->SetLocation(Point{ amountBoxX, amountBoxY });

        AmountBox->SetValue(1);
        // AmountBox.ValueTextBox.KeepFocus = true;
        // AmountBox.ValueTextBox.SetFocus();
        // AmountBox.ValueTextBox.TextBox.KeyPress += AmountBox_KeyPress;
    }

    void DXItemAmountWindow::AmountBox_KeyPress(void* sender, KeyPressEventArgs& e)
    {
        char keyChar = e.KeyChar;
        
        switch (static_cast<Keys>(keyChar))
        {
            case Keys::Enter:
                e.Handled = true;
                // ConfirmButton->InvokeMouseClick();
                // DXTextBox::ActiveTextBox = nullptr;
                break;
                
            case Keys::Escape:
                e.Handled = true;
                // CloseButton->InvokeMouseClick();
                // DXTextBox::ActiveTextBox = nullptr;
                break;
        }
    }

    void DXItemAmountWindow::AmountBox_ValueChanged(void* sender, void* e)
    {
        Amount = AmountBox->GetValue();

        if (Amount <= 0)
        {
            // AmountBox.ValueTextBox.BorderColour = Color.Red;
        }
        else if (Amount == AmountBox->GetMaxValue())
        {
            // AmountBox.ValueTextBox.BorderColour = Color.Orange;
        }
        else
        {
            // AmountBox.ValueTextBox.BorderColour = Color.Green;
        }

        if (ConfirmButton != nullptr)
            ConfirmButton->SetEnabled(Amount > 0);

        // Check if currency item and refresh
        // if (CEnvir::IsCurrencyItem(item.Info))
        // {
        //     item.Count = Amount;
        //     ItemCell->RefreshItem();
        // }
    }

    void DXItemAmountWindow::Dispose(bool disposing)
    {
        DXWindow::Dispose(disposing);

        if (disposing)
        {
            if (ConfirmButton != nullptr)
            {
                if (!ConfirmButton->GetIsDisposed())
                    ConfirmButton->Dispose();
                delete ConfirmButton;
                ConfirmButton = nullptr;
            }

            if (AmountBox != nullptr)
            {
                if (!AmountBox->GetIsDisposed())
                    AmountBox->Dispose();
                delete AmountBox;
                AmountBox = nullptr;
            }

            if (ItemCell != nullptr)
            {
                if (!ItemCell->GetIsDisposed())
                    ItemCell->Dispose();
                delete ItemCell;
                ItemCell = nullptr;
            }
        }
    }

} // namespace Client::Controls
