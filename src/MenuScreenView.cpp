#include <algorithm>
#include <sstream>
#include "ResourceManager.hpp"
#include "MenuScreenView.hpp"
#include "Game.hpp"
#include "Cursor.hpp"

namespace fknd {
	
	MenuScreenView::MenuScreenView() : ScreenView() {

		mFont = ResourceManager::GetFont(PATH_FONT);
		mCursor = std::make_shared<Cursor>(*mFont);
	
		mBackgroundTex = ResourceManager::GetTexture(PATH_TEX_BG);
		mBackground = std::make_shared<sf::Sprite>(sf::Sprite(*mBackgroundTex));
		mBackground->setColor(MENU_BG_TINT);


		mBgmTxt = std::make_shared<sf::Text>(*mFont);
		mBgmTxt->setString(std::string(MENU_VOL_MUS_STR));
		mBgmTxt->setCharacterSize(MENU_TXT_CHAR_SZ);
		mBgmTxt->setFillColor(MENU_TXT_FILLCOL);
		mBgmTxt->setOutlineColor(MENU_TXT_OUTCOL);
		mBgmTxt->setOutlineThickness(MENU_TXT_OUTLINE_SZ);
		mBgmTxt->setPosition({176.0f, 384.0f + MENU_TXT_OFFSET_Y});
		
		mSfxTxt = std::make_shared<sf::Text>(*mFont);
		mSfxTxt->setString(std::string(MENU_VOL_SFX_STR));
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
		mDrawables.push_back(mCursor);
	}

	bool MenuScreenView::Update(MenuScreenUpdate update) {
		if (update.menu)
			return false;
		return true;
	}


	bool MenuScreenView::Update() { return false; }
}

