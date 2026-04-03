#pragma once
#include <string>
#include "ResourceManager.hpp"
#include "ScreenView.hpp"
#include "Cursor.hpp"
#include "Common.hpp"

namespace fknd {
	
	class EndScreenView : public ScreenView {
		public:
		
			struct EndScreenUpdate {
				bool      left;
				bool      right;
				bool      up;
				bool      down;
				bool      action;
				uint32_t& score;
				std::vector<ResourceManager::ScoreEntry>& ranking;
			};
			
			EndScreenView();

			bool Update(const EndScreenUpdate& update);
			
		private:
			
			
			struct ScoreEntryText {
				std::shared_ptr<sf::Text> name;
				std::shared_ptr<sf::Text> score;
			};

			std::shared_ptr<sf::Font>           mFont;
			std::shared_ptr<sf::Text>           mTitleTxt;
			std::shared_ptr<sf::Text>           mContTxt;
			std::shared_ptr<sf::Texture>        mBackgroundTex;
			std::shared_ptr<sf::Sprite>         mBackground;
			std::shared_ptr<Cursor>             mCursor;
	
			std::vector<ScoreEntryText> mRankingTxt;
			bool mIsRankingDraw;
			bool mIsNameSet;
	
			bool DrawPlayerRanking(const std::vector<ResourceManager::ScoreEntry>& ranking);
			std::string* GetGameEntryName(std::vector<ResourceManager::ScoreEntry>& ranking); 
			std::string PadZeroScore(uint32_t score, uint32_t digits);
			bool Update();
	};

}