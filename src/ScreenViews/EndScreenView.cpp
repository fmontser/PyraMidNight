#include <algorithm>
#include <sstream>
#include "UserDataManager.hpp"
#include "ResourceManager.hpp"
#include "EndScreenView.hpp"
#include "Game.hpp"
#include "Cursor.hpp"

namespace pyramidnight {
	
	EndScreenView::EndScreenView() : ScreenView() {
		mIsRankingDraw = false;
		mIsNameSet =  false;
		mFont = ResourceManager::GetFont(PATH_FONT);
		mCursor = std::make_shared<Cursor>(*mFont, mClock);
	
		mTitleTxt = std::make_shared<sf::Text>(*mFont);
		mTitleTxt->setString(std::string(END_STR));
		mTitleTxt->setCharacterSize(END_TXT_CHAR_SZ);
		mTitleTxt->setFillColor(END_TXT_FILLCOL);
		mTitleTxt->setOutlineColor(END_TXT_OUTCOL);
		mTitleTxt->setOutlineThickness(END_TXT_OUTLINE_SZ);
		mTitleTxt->setPosition({100.f, 100.f});

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
	
			mRankingTxt.push_back({nameEntry, scoreEntry, false});
		}
		
		mContTxt = std::make_shared<sf::Text>(*mFont);
		mContTxt->setString(std::string(END_CONT_STR));
		mContTxt->setCharacterSize(END_TXT_CONT_CHAR_SZ);
		mContTxt->setFillColor(END_TXT_FILLCOL);
		mContTxt->setOutlineColor(END_TXT_OUTCOL);
		mContTxt->setOutlineThickness(END_TXT_OUTLINE_SZ);
		mContTxt->setPosition({100.f, 650.f});
	
		mBackgroundTex = ResourceManager::GetTexture(PATH_TEX_BG);
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

	bool EndScreenView::Update(const EndScreenUpdate& update) {
		if (!mIsRankingDraw) {
			auto& ranking = UserDataManager::GetUserData().ranking;
			ranking.push_back({std::string(END_EMPTY_NAME_STR), update.score, true});
			UserDataManager::SortRanking();
			if (ranking.size() > GAME_RANK_SIZE)
				ranking.pop_back();
			mIsRankingDraw = DrawPlayerRanking();
			mRecordNameTxt = FindRecordNameTxt();
			if (mRecordNameTxt != nullptr)
				mContTxt->setScale({0,0});
			else
				mIsNameSet = true;
		}
		if (!mIsNameSet) {
			if (!mCursor->Update(WrapCursorUpdate(update))) {
				SetRecordName();
				mContTxt->setScale({1,1});
				mIsNameSet = true;
				return true;
			}
		}
		if (mIsNameSet && update.action)
		return false;
		return true;
	}
	
	bool EndScreenView::DrawPlayerRanking() {
		size_t i = 0;
		
		for (auto& entry : UserDataManager::GetUserData().ranking) {
			if (i < mRankingTxt.size()) {
				mRankingTxt[i].name->setString(entry.name);
				mRankingTxt[i].score->setString(PadZeroScore(entry.score, 10));
				mRankingTxt[i].actual = entry.actual;
			}
			i++;
		}
		return true;
	}
	
	std::string EndScreenView::PadZeroScore(uint32_t score, uint32_t digits) {
		std::ostringstream ss;
	
		ss << std::setw(digits) << std::setfill('0') << score;
		return ss.str();
	}
	
	std::shared_ptr<sf::Text> EndScreenView::FindRecordNameTxt() {
		for (auto& text : mRankingTxt) {
			if (text.actual)
			return text.name;
		}
		return nullptr;
	}

	void EndScreenView::SetRecordName() {
		auto& ranking = UserDataManager::GetUserData().ranking;
		auto entry = std::find_if(ranking.begin(), ranking.end(),
		[](const UserDataManager::ScoreEntry& entry){
			return entry.actual == true;
		});
		entry->name = mRecordNameTxt->getString();
	}

	Cursor::CursorUpdate EndScreenView::WrapCursorUpdate(const EndScreenUpdate &update) {
		return {
			update.left,
			update.right,
			update.up,
			update.down,
			update.action,
			mRecordNameTxt
		};
	}

	bool EndScreenView::Update() { return false; }
}

