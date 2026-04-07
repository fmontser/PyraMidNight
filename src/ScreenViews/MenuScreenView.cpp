#include <string>
#include <algorithm>
#include "UserDataManager.hpp"
#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include "MenuScreenView.hpp"

namespace pyramidnight {
	
	MenuScreenView::MenuScreenView() : ScreenView() {
		mBgmVolume = AudioManager::GetBgmVolume();
		mSfxVolume = AudioManager::GetSfxVolume();
		mOption = Option::BGM;
		mOptionIndex = 0;

		mFont = ResourceManager::GetFont(PATH_FONT);
	
		mBackgroundTex = ResourceManager::GetTexture(PATH_TEX_BG);
		mBackground = std::make_shared<sf::Sprite>(sf::Sprite(*mBackgroundTex));
		mBackground->setColor(MENU_BG_TINT);

		mBgmTxt = std::make_shared<sf::Text>(*mFont);
		mBgmTxt->setString(std::string(MENU_VOL_MUS_STR)
			.append(std::to_string(mBgmVolume)));
		mBgmTxt->setCharacterSize(MENU_TXT_CHAR_SZ);
		mBgmTxt->setFillColor(MENU_TXT_FILLCOL);
		mBgmTxt->setOutlineColor(MENU_TXT_OUTCOL);
		mBgmTxt->setOutlineThickness(MENU_TXT_OUTLINE_SZ);
		mBgmTxt->setPosition({176.0f, 384.0f + MENU_TXT_OFFSET_Y});
		
		mSfxTxt = std::make_shared<sf::Text>(*mFont);
		mSfxTxt->setString(std::string(MENU_VOL_SFX_STR)
			.append(std::to_string(mSfxVolume)));
		mSfxTxt->setCharacterSize(MENU_TXT_CHAR_SZ);
		mSfxTxt->setFillColor(MENU_TXT_FILLCOL);
		mSfxTxt->setOutlineColor(MENU_TXT_OUTCOL);
		mSfxTxt->setOutlineThickness(MENU_TXT_OUTLINE_SZ);
		mSfxTxt->setPosition({176.0f, 448.0f + MENU_TXT_OFFSET_Y});

		mExitTxt = std::make_shared<sf::Text>(*mFont);
		mExitTxt->setString(std::string(MENU_EXIT_STR));
		mExitTxt->setCharacterSize(MENU_TXT_CHAR_SZ);
		mExitTxt->setFillColor(MENU_TXT_FILLCOL);
		mExitTxt->setOutlineColor(MENU_TXT_OUTCOL);
		mExitTxt->setOutlineThickness(MENU_TXT_OUTLINE_SZ);
		mExitTxt->setPosition({176.0f, 512.0f + MENU_TXT_OFFSET_Y});

		mDrawables.push_back(mBackground);
		mDrawables.push_back(mBgmTxt);
		mDrawables.push_back(mSfxTxt);
		mDrawables.push_back(mExitTxt);

		mTexts.push_back(mBgmTxt);
		mTexts.push_back(mSfxTxt);
		mTexts.push_back(mExitTxt);
		InvertOptionColors(mBgmTxt);
	}

	bool MenuScreenView::Update(const MenuScreenUpdate& update) {
		SelectOption(update.up, update.down);
		if (mOption == Option::BGM && (update.left || update.right)) {
			if (update.left) UpdateBgmVolume(-MENU_VOL_STEP_SZ);
			else if (update.right) UpdateBgmVolume(MENU_VOL_STEP_SZ);
		}
		else if (mOption == Option::SFX && (update.left || update.right)) {
			if (update.left) UpdateSfxVolume(-MENU_VOL_STEP_SZ);
			else if (update.right) UpdateSfxVolume(MENU_VOL_STEP_SZ);
		}
		else if (mOption == Option::EXIT && update.action)
			exit(0);
		else if (update.menu)
			return false;
		return true;
	}

	void MenuScreenView::UpdateBgmVolume(float volume) {
		mBgmVolume = std::clamp( mBgmVolume + volume, VOL_AUD_MIN, VOL_AUD_MAX);
		mBgmTxt->setString(std::string(MENU_VOL_MUS_STR).append(std::to_string(mBgmVolume)));

		AudioManager::SetBgmVolume(mBgmVolume);
		UserDataManager::SaveBgmVolume(AudioManager::GetBgmVolume());
		auto sb = ResourceManager::GetAudio(PATH_AUD_CURSOR);
		AudioManager::Play({sb, VOL_AUD_CURSOR, PolySound::Type::SFX, false});

	}

	void MenuScreenView::UpdateSfxVolume(float volume) {
		mSfxVolume = std::clamp( mSfxVolume + volume, VOL_AUD_MIN, VOL_AUD_MAX);
		mSfxTxt->setString(std::string(MENU_VOL_SFX_STR).append(std::to_string(mSfxVolume)));
		
		AudioManager::SetSfxVolume(mSfxVolume);
		UserDataManager::SaveSfxVolume(AudioManager::GetSfxVolume());
		auto sb = ResourceManager::GetAudio(PATH_AUD_CURSOR);
		AudioManager::Play({sb, VOL_AUD_CURSOR, PolySound::Type::SFX, false});
	}

	void MenuScreenView::SelectOption(bool up, bool down) {
		if (up & !down)
			mOptionIndex = (mOptionIndex - 1 + MENU_OPT_MAX) % MENU_OPT_MAX;
		else if (!up && down)
			mOptionIndex =  (mOptionIndex + 1) % MENU_OPT_MAX;
		else
			return;
		auto sb = ResourceManager::GetAudio(PATH_AUD_CURSOR);
		AudioManager::Play({sb, VOL_AUD_CURSOR, PolySound::Type::SFX, false});
		mOption = static_cast<Option>(mOptionIndex);
		switch (mOption) {
			case BGM: InvertOptionColors(mBgmTxt); break;
			case SFX: InvertOptionColors(mSfxTxt); break;
			case EXIT: InvertOptionColors(mExitTxt); break;
			default: break;
		}
	}

	void MenuScreenView::InvertOptionColors(const std::shared_ptr<sf::Text>& option) {
		for (auto& text : mTexts){
			if (text.get() == option.get()){
				text->setFillColor(MENU_TXT_OUTCOL);
				text->setOutlineColor(MENU_TXT_FILLCOL);
			} else {
				text->setFillColor(MENU_TXT_FILLCOL);
				text->setOutlineColor(MENU_TXT_OUTCOL);
			}
		}
	}

	bool MenuScreenView::Update() { return false; }
}

