#include "TitleScreenView.hpp"
#include "Game.hpp"

namespace fknd {
	
	TitleScreenView::TitleScreenView() : ScreenView() {
		//TODO filesystem exception control
		mFont = std::make_shared<sf::Font>(PATH_FONT);
	
		mTitleTxt = std::make_shared<sf::Text>(*mFont);
		mTitleTxt->setString(std::string(TITLE_STR));
		mTitleTxt->setCharacterSize(TITLE_TXT_CHAR_SZ);
		mTitleTxt->setFillColor(TITLE_TXT_FILLCOL);
		mTitleTxt->setPosition({100.f, 100.f});
		mTitleTxt->setOutlineColor(TITLE_TXT_OUTCOL);
		mTitleTxt->setOutlineThickness(TITLE_TXT_OUTLINE_SZ);
	
		mCreditsTxt = std::make_shared<sf::Text>(*mFont);
		mCreditsTxt->setString(std::string(TITLE_CREDITS_STR).append("0"));
		mCreditsTxt->setCharacterSize(TITLE_TXT_CREDITS_CHAR_SZ);
		mCreditsTxt->setFillColor(TITLE_TXT_FILLCOL);
		mCreditsTxt->setPosition({100.f, 500.f});
		mCreditsTxt->setOutlineColor(TITLE_TXT_OUTCOL);
		mCreditsTxt->setOutlineThickness(TITLE_TXT_OUTLINE_SZ);
	
		mStartTxt = std::make_shared<sf::Text>(*mFont);
		mStartTxt->setScale({0,0});
		mStartTxt->setString(std::string(TITLE_START_STR));
		mStartTxt->setCharacterSize(TITLE_TXT_START_CHAR_SZ);
		mStartTxt->setFillColor(TITLE_TXT_FILLCOL);
		mStartTxt->setPosition({130.f, 600.f});
		mStartTxt->setOutlineColor(TITLE_TXT_OUTCOL);
		mStartTxt->setOutlineThickness(TITLE_TXT_OUTLINE_SZ);
	
		mBackgroundTex = std::make_shared<sf::Texture>(sf::Texture(PATH_TEX_BG));
		mBackground = std::make_shared<sf::Sprite>(sf::Sprite(*mBackgroundTex));
		mBackground->setColor(TITLE_BG_TINT);
	
		mDrawables.push_back(mBackground);
		mDrawables.push_back(mTitleTxt);
		mDrawables.push_back(mCreditsTxt);
		mDrawables.push_back(mStartTxt);
	}

	bool TitleScreenView::Update(TitleScreenUpdate update)
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
		if (credits < GAME_MAX_CREDITS)
			credits++;
		mCreditsStr = std::string(TITLE_CREDITS_STR).append(
			std::to_string(credits));
	}
	void TitleScreenView::ShowStartText() {
		mStartTxt->setScale({1,1});
		mCreditsTxt->setString(mCreditsStr);
	}
	
	bool TitleScreenView::Update() { return false;}
}