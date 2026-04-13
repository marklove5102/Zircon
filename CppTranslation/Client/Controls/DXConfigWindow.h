#pragma once

#include "../Common/CSharpCompat.h"
#include "DXWindow.h"
#include "DXKeyBindWindow.h"
#include "DXTabControl.h"
#include "DXTab.h"
#include "DXCheckBox.h"
#include "DXComboBox.h"
#include "DXNumberBox.h"
#include "DXTextBox.h"
#include "DXLabel.h"
#include "DXColourControl.h"
#include "DXButton.h"

namespace Client::Controls
{
    class DXConfigWindow final : public DXWindow
    {
    public:
        // Properties
        static DXConfigWindow* ActiveConfig;
        DXKeyBindWindow* KeyBindWindow;

        // Graphics Tab
        DXTab* GraphicsTab;
        DXCheckBox* FullScreenCheckBox;
        DXCheckBox* VSyncCheckBox;
        DXCheckBox* LimitFPSCheckBox;
        DXCheckBox* ClipMouseCheckBox;
        DXCheckBox* DebugLabelCheckBox;
        DXCheckBox* SmoothMoveCheckBox;
        DXComboBox* GameSizeComboBox;
        DXComboBox* LanguageComboBox;

        // Sound Tab
        DXTab* SoundTab;
        DXNumberBox* SystemVolumeBox;
        DXNumberBox* MusicVolumeBox;
        DXNumberBox* SpellVolumeBox;
        DXNumberBox* PlayerVolumeBox;
        DXNumberBox* MonsterVolumeBox;
        DXCheckBox* BackgroundSoundBox;

        // Game Tab
        DXTab* GameTab;
        DXCheckBox* ItemNameCheckBox;
        DXCheckBox* MonsterNameCheckBox;
        DXCheckBox* PlayerNameCheckBox;
        DXCheckBox* UserHealthCheckBox;
        DXCheckBox* MonsterHealthCheckBox;
        DXCheckBox* DamageNumbersCheckBox;
        DXCheckBox* EscapeCloseAllCheckBox;
        DXCheckBox* ShiftOpenChatCheckBox;
        DXCheckBox* RightClickDeTargetCheckBox;
        DXCheckBox* MonsterBoxVisibleCheckBox;
        DXCheckBox* LogChatCheckBox;
        DXCheckBox* DrawEffectsCheckBox;
        DXCheckBox* DrawParticlesCheckBox;
        DXCheckBox* DrawWeatherCheckBox;
        DXCheckBox* DisplayHelmetCheckBox;
        DXCheckBox* HideChatBarCheckBox;
        DXButton* KeyBindButton;

        // Network Tab
        DXTab* NetworkTab;
        DXCheckBox* UseNetworkConfigCheckBox;
        DXTextBox* IPAddressTextBox;
        DXNumberBox* PortBox;

        // Colour Tab
        DXTab* ColourTab;
        DXColourControl* LocalForeColourBox;
        DXColourControl* GMWhisperInForeColourBox;
        DXColourControl* WhisperInForeColourBox;
        DXColourControl* WhisperOutForeColourBox;
        DXColourControl* GroupForeColourBox;
        DXColourControl* GuildForeColourBox;
        DXColourControl* ShoutForeColourBox;
        DXColourControl* GlobalForeColourBox;
        DXColourControl* ObserverForeColourBox;
        DXColourControl* HintForeColourBox;
        DXColourControl* SystemForeColourBox;
        DXColourControl* GainsForeColourBox;
        DXColourControl* AnnouncementForeColourBox;
        
        DXColourControl* LocalBackColourBox;
        DXColourControl* GMWhisperInBackColourBox;
        DXColourControl* WhisperInBackColourBox;
        DXColourControl* WhisperOutBackColourBox;
        DXColourControl* GroupBackColourBox;
        DXColourControl* GuildBackColourBox;
        DXColourControl* ShoutBackColourBox;
        DXColourControl* GlobalBackColourBox;
        DXColourControl* ObserverBackColourBox;
        DXColourControl* HintBackColourBox;
        DXColourControl* SystemBackColourBox;
        DXColourControl* GainsBackColourBox;
        DXColourControl* AnnouncementBackColourBox;
        
        DXButton* ResetColoursButton;

        void OnVisibleChanged(bool oValue, bool nValue) override;
        void OnParentChanged(DXControl* oValue, DXControl* nValue) override;
        
        WindowType GetType() const override { return WindowType::ConfigBox; }
        bool GetCustomSize() const override { return false; }
        bool GetAutomaticVisibility() const override { return false; }

        DXConfigWindow();
        ~DXConfigWindow() override;

    private:
        DXTabControl* TabControl;
        DXButton* SaveButton;
        DXButton* CancelButton;
    };
}
