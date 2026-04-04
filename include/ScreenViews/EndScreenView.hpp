#pragma once
#include <string>
#include "UserDataManager.hpp"
#include "ResourceManager.hpp"
#include "ScreenView.hpp"
#include "Cursor.hpp"
#include "Common.hpp"

namespace pyramidnight {
	
	class EndScreenView : public ScreenView {
		public:
		

			struct EndScreenUpdate {
				bool         left;
				bool         right;
				bool         up;
				bool         down;
				bool         action;
				uint32_t&    score;
			};
			
			EndScreenView();

			bool Update(const EndScreenUpdate& update);
			
		private:
			struct ScoreEntryText {
				std::shared_ptr<sf::Text> name;
				std::shared_ptr<sf::Text> score;
				bool                      actual;
			};
			
			std::shared_ptr<sf::Font>    mFont;
			std::shared_ptr<sf::Text>    mTitleTxt;
			std::shared_ptr<sf::Text>    mContTxt;
			std::shared_ptr<sf::Texture> mBackgroundTex;
			std::shared_ptr<sf::Sprite>  mBackground;
			std::shared_ptr<Cursor>      mCursor;
	
			std::vector<ScoreEntryText>  mRankingTxt;
			std::shared_ptr<sf::Text>    mRecordNameTxt;
			bool                         mIsRankingDraw;
			bool                         mIsNameSet;
	
			bool                      DrawPlayerRanking();
			std::string               PadZeroScore(uint32_t score, uint32_t digits);
			std::shared_ptr<sf::Text> FindRecordNameTxt();
			void                      SetRecordName();
			Cursor::CursorUpdate      WrapCursorUpdate(const EndScreenUpdate& update);
			bool Update();
	};

}