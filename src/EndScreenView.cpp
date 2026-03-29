#include <algorithm>
#include <sstream>
#include "EndScreenView.hpp"
#include "Game.hpp"
#include "Cursor.hpp"

namespace fknd {
	
	EndScreenView::EndScreenView() : ScreenView() {
		mIsRankingDraw = false;
		mIsNameSet =  false;
	
		//TODO filesystem exception control
		mFont = std::make_shared<sf::Font>(PATH_FONT);
		mCursor = std::make_shared<Cursor>(*mFont);
	
		mTitleTxt = std::make_shared<sf::Text>(*mFont);
		mTitleTxt->setString(std::string(END_STR));
		mTitleTxt->setCharacterSize(END_TXT_CHAR_SZ);
		mTitleTxt->setFillColor(END_TXT_FILLCOL);
		mTitleTxt->setOutlineColor(END_TXT_OUTCOL);
		mTitleTxt->setOutlineThickness(END_TXT_OUTLINE_SZ);
		mTitleTxt->setPosition({100.f, 100.f});
	
		//TODO make dynamic score ranking
		auto rankingEntryPos = sf::Vector2f({100.0f, 160.0f});
		for (size_t i = 0; i < 10; i++) {
			auto nameEntry = std::make_shared<sf::Text>(*mFont);
			nameEntry->setString("   ");
			auto textOffset = sf::Vector2f({160.0f, 40.0f});
	
			rankingEntryPos.y += textOffset.y;
			nameEntry->setCharacterSize(END_TXT_RANK_CHAR_SZ);
			nameEntry->setFillColor(sf::Color::White);
			nameEntry->setOutlineColor(sf::Color::Blue);
			nameEntry->setOutlineThickness(END_TXT_RANK_OUTLINE_SZ);
			nameEntry->setPosition(rankingEntryPos);
	
			auto scoreEntry = std::make_shared<sf::Text>(*mFont);
			scoreEntry->setString("0000000000");
	
			rankingEntryPos.x += textOffset.x;
			scoreEntry->setCharacterSize(END_TXT_RANK_CHAR_SZ);
			scoreEntry->setFillColor(sf::Color::White);
			scoreEntry->setOutlineColor(sf::Color::Blue);
			scoreEntry->setOutlineThickness(END_TXT_RANK_OUTLINE_SZ);
			scoreEntry->setPosition(rankingEntryPos);
			rankingEntryPos.x -= textOffset.x;
	
			mRankingTxt.push_back({nameEntry, scoreEntry});
		}
		
		mContTxt = std::make_shared<sf::Text>(*mFont);
		mContTxt->setScale({0,0});
		mContTxt->setString(std::string(END_CONT_STR));
		mContTxt->setCharacterSize(END_TXT_CONT_CHAR_SZ);
		mContTxt->setFillColor(END_TXT_FILLCOL);
		mContTxt->setOutlineColor(END_TXT_OUTCOL);
		mContTxt->setOutlineThickness(END_TXT_OUTLINE_SZ);
		mContTxt->setPosition({100.f, 650.f});
	
		mBackgroundTex = std::make_shared<sf::Texture>(sf::Texture(PATH_TEX_BG));
		mBackground = std::make_shared<sf::Sprite>(sf::Sprite(*mBackgroundTex));
		mBackground->setColor(END_BG_TINT);
	
		mDrawables.push_back(mBackground);
		mDrawables.push_back(mTitleTxt);
		mDrawables.push_back(mContTxt);
	
		for (const auto& entry : mRankingTxt) {
			mDrawables.push_back(entry.name);
			mDrawables.push_back(entry.score);
		}
	
		mDrawables.push_back(mCursor);
	}
	
	bool EndScreenView::Update(Game& game) {
		auto& frameInput = game.GetInputManager().FetchInput();
		auto& window = game.GetRenderManager().GetWindow();
	
		if (!mIsRankingDraw) {
			mIsRankingDraw = SetGameRanking(game);
				
			//Find record for cursor
			for (auto& text : mRankingTxt) {
				if (text.name->getString() == "   ")
					mCursor->SetEntry(text.name);
			}
		}
		if (frameInput.close)
			window.close();
		if (!mIsNameSet) {
			if (frameInput.left)
			mCursor->Update(Cursor::Input::LEFT);
			else if (frameInput.right)
			mCursor->Update(Cursor::Input::RIGHT);
			else if (frameInput.up)
			mCursor->Update(Cursor::Input::UP);
			else if (frameInput.down)
			mCursor->Update(Cursor::Input::DOWN);
			else if (frameInput.action) {
				mIsNameSet = mCursor->Accept(GetGameEntryName(game));
				mContTxt->setScale({1,1});
				return true;
			}
		}
		if (frameInput.action && mIsNameSet)
			return false;
		return true;
	}
	
	bool EndScreenView::SetGameRanking(Game& game) {
		auto ranking = game.GetRanking();
		size_t i = 0;
	
		for (auto& gameEntry : ranking) {
			if (i < mRankingTxt.size()) {
				mRankingTxt[i].name->setString(gameEntry.name);
				mRankingTxt[i].score->setString(PadZeroScore(gameEntry.score, 10));
			}
			i++;
		}
		return true;
	}
	
	std::string* EndScreenView::GetGameEntryName(Game &game) {
		for (auto& gameEntry : game.GetRanking()) {
			if (gameEntry.name == "   ")
				return &gameEntry.name;
		}
		return nullptr;
	}
	
	std::string EndScreenView::PadZeroScore(uint32_t score, uint32_t digits) {
		std::ostringstream ss;
	
		ss << std::setw(digits) << std::setfill('0') << score;
		return ss.str();
	}

}

