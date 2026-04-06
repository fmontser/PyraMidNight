#include "ResourceManager.hpp"
#include "RenderManager.hpp"
#include "Blink.hpp"
#include "TitleScreenView.hpp"
#include "Game.hpp"
#include "AudioManager.hpp"

namespace pyramidnight {
	
	TitleScreenView::TitleScreenView() : ScreenView() {
		mStartTextVisible = false;
		mFont = ResourceManager::GetFont(PATH_FONT);
	
		mTitleTxt = std::make_shared<sf::Text>(*mFont);
		mTitleTxt->setString(std::string(TITLE_STR));
		mTitleTxt->setCharacterSize(TITLE_TXT_CHAR_SZ);
		mTitleTxt->setFillColor(TITLE_TXT_FILLCOL);
		mTitleTxt->setPosition({55.0f, 100.0f});
		mTitleTxt->setOutlineColor(TITLE_TXT_OUTCOL);
		mTitleTxt->setOutlineThickness(TITLE_TXT_OUTLINE_SZ);

		mCreditsTxt = std::make_shared<sf::Text>(*mFont);
		mCreditsTxt->setString(std::string(TITLE_CREDITS_STR).append("0"));
		mCreditsTxt->setCharacterSize(TITLE_TXT_CREDITS_CHAR_SZ);
		mCreditsTxt->setFillColor(TITLE_TXT_FILLCOL);
		mCreditsTxt->setPosition({100.0f, 500.0f});
		mCreditsTxt->setOutlineColor(TITLE_TXT_OUTCOL);
		mCreditsTxt->setOutlineThickness(TITLE_TXT_OUTLINE_SZ);
	
		mStartTxt = std::make_shared<sf::Text>(*mFont);
		mStartTxt->setScale({0,0});
		mStartTxt->setString(std::string(TITLE_START_STR));
		mStartTxt->setCharacterSize(TITLE_TXT_START_CHAR_SZ);
		mStartTxt->setFillColor(TITLE_TXT_FILLCOL);
		mStartTxt->setPosition({130.0f, 600.0f});
		mStartTxt->setOutlineColor(TITLE_TXT_OUTCOL);
		mStartTxt->setOutlineThickness(TITLE_TXT_OUTLINE_SZ);
	
		mBackgroundTex = ResourceManager::GetTexture(PATH_TEX_BG);
		mBackground = std::make_shared<sf::Sprite>(sf::Sprite(*mBackgroundTex));
		mBackground->setColor(TITLE_BG_TINT);
	
		mDrawables.push_back(mBackground);
		mDrawables.push_back(mTitleTxt);
		mDrawables.push_back(mCreditsTxt);
		mDrawables.push_back(mStartTxt);
		AudioManager::Play({PATH_AUD_MUSIC_0, VOL_AUD_MUSIC_0, PolySound::Type::BGM, true});
	}

	bool TitleScreenView::Update(const TitleScreenUpdate& update)
	{
		if (update.coin) {
			UpdateCredits(update.credits);
			if (update.credits > 0)
				ShowStartText();
		}
		if (update.action && update.credits > 0)
			return false;
		return true;
	}

	void TitleScreenView::UpdateCredits(uint8_t& credits) {
		if (credits < GAME_MAX_CREDITS) {
			credits++;
			AudioManager::Play({PATH_AUD_COIN_IN, VOL_AUD_COIN_IN, PolySound::Type::SFX, false});
		}
		mCreditsStr = std::string(TITLE_CREDITS_STR).append(
			std::to_string(credits));
	}
	
	void TitleScreenView::ShowStartText() {
		if (!mStartTextVisible) {
			RenderManager::DisplayEffect(std::make_unique<Blink>(-1.0f, 0.3f, mStartTxt));
			mStartTextVisible = true;
		}
		mCreditsTxt->setString(mCreditsStr);
	}

	bool TitleScreenView::Update() { return false;}
}