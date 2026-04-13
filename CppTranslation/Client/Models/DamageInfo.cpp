#include "DamageInfo.h"
#include "../Envir/CEnvir.h"
#include "../Scenes/GameScene.h"

using namespace System;
using namespace System::Drawing;
using namespace Client::Models;
using namespace Client::Envir;
using namespace Client::Scenes;
using namespace Library;

// Static constructor
DamageInfo::!DamageInfo()
{
}

DamageInfo::DamageInfo()
{
    _StartTime = CEnvir::Now;
    _AppearDelay = TimeSpan::FromMilliseconds(500);
    _ShowDelay = TimeSpan::FromSeconds(1);
    _HideDelay = TimeSpan::FromMilliseconds(250);
    
    BlueWidth = 9;
    RedWidth = 9;
    GreenWidth = 11;
    OrangeWidth = 13;
    WhiteWidth = 20;
    
    BlueIndex = 71;
    RedIndex = 72;
    GreenIndex = 73;
    OrangeIndex = 74;
    WhiteIndex = 75;
    
    DrawHeight = 80;
    Visible = true;
    Opacity = 0.0f;
}

void DamageInfo::OnValueChanged(int oValue, int nValue)
{
    ValueChanged?.Invoke(this, EventArgs::Empty);
}

void DamageInfo::OnBlockChanged(bool oValue, bool nValue)
{
    BlockChanged?.Invoke(this, EventArgs::Empty);
}

void DamageInfo::OnMissChanged(bool oValue, bool nValue)
{
    MissChanged?.Invoke(this, EventArgs::Empty);
}

void DamageInfo::OnCriticalChanged(bool oValue, bool nValue)
{
    CriticalChanged?.Invoke(this, EventArgs::Empty);
}

int DamageInfo::Bottom()
{
    return DrawY - 20;
}

void DamageInfo::Process(DamageInfo^ previous)
{
    if (Library == nullptr) return;

    TimeSpan visibleTime = CEnvir::Now - StartTime;
    int oldY = DrawY;

    if (visibleTime < AppearDelay)
    {
        decimal percent = (decimal)visibleTime.Ticks / (decimal)AppearDelay.Ticks;
        DrawY = (int)(DrawHeight * (double)percent);
        Opacity = (float)((double)percent * 3.0);
    }
    else if (visibleTime < AppearDelay + ShowDelay)
    {
        DrawY = DrawHeight;
        Opacity = 1.0f;
    }
    else if (visibleTime < AppearDelay + ShowDelay + HideDelay)
    {
        visibleTime -= AppearDelay + ShowDelay;
        decimal percent = (decimal)visibleTime.Ticks / (decimal)HideDelay.Ticks;
        DrawY = DrawHeight + (int)(40.0 * (double)percent);
        Opacity = 1.0f - (float)(double)percent;
    }
    else
    {
        Visible = false;
        return;
    }

    if (previous != nullptr && previous->Visible)
        DrawY = Math::Min(DrawY, previous->Bottom());

    if (oldY != DrawY && GameScene::Game != nullptr && GameScene::Game->MapControl != nullptr)
        GameScene::Game->MapControl->TextureValid = false;
}

void DamageInfo::Draw(int drawX, int drawY)
{
    if (Library == nullptr) return;

    drawY -= DrawY + 20;
    drawX += 24;

    if (Value == 0)
    {
        if (Miss)
        {
            Size size = Library->GetSize(76);
            drawX -= size.Width / 2;
            Library->Draw(76, drawX, drawY, Color::White, false, Opacity, ImageType::Image);
        }
        else if (Block)
        {
            Size size = Library->GetSize(77);
            drawX -= size.Width / 2;
            Library->Draw(77, drawX, drawY, Color::White, false, Opacity, ImageType::Image);
        }
    }
    else
    {
        String^ text = Value.ToString("+ #0;-#0");
        int index, width;

        if (Value <= -1000)
        {
            index = WhiteIndex;
            width = WhiteWidth;
        }
        else if (Value <= -500)
        {
            index = OrangeIndex;
            width = OrangeWidth;
        }
        else if (Value <= -100)
        {
            index = GreenIndex;
            width = GreenWidth;
        }
        else if (Value < 0)
        {
            index = RedIndex;
            width = RedWidth;
        }
        else
        {
            index = BlueIndex;
            width = BlueWidth;
        }

        drawX -= width * text->Length / 2;

        if (Critical && Value < 0)
        {
            Size size = Library->GetSize(78);
            drawX -= size.Width / 2;
            Library->Draw(78, drawX, drawY, Color::White, false, Opacity, ImageType::Image);
            drawX += size.Width + 5;
        }

        Size charSize = Library->GetSize(index);

        for (int i = 0; i < text->Length; i++)
        {
            int number;
            Char c = text[i];

            if (!Int32::TryParse(c.ToString(), [out] number))
            {
                if (c == '+')
                    number = 10;
                else if (c == '-')
                    number = 11;
                else
                    continue;
            }

            Rectangle rect(width * number, 0, Math::Min(charSize.Width - width * number, width), charSize.Height);
            Library->Draw(index, drawX, drawY, Color::White, rect, Opacity, ImageType::Image);
            drawX += width;
        }
    }
}

// Static constructor implementation
DamageInfo::DamageInfo(int dummy) // Dummy parameter to distinguish from instance constructor
{
    if (CEnvir::LibraryList->ContainsKey(LibraryFile::Interface))
        Library = CEnvir::LibraryList[LibraryFile::Interface];
}
