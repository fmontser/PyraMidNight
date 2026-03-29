// Game state machine
#pragma once
#include <cstdint>
#include "TitleScreenView.hpp"
#include "RoundScreenView.hpp"
#include "EndScreenView.hpp"
#include "InputManager.hpp"
#include "RenderManager.hpp"
#include "Common.hpp"

namespace fknd {

	class Game {
		public:
			enum class State {
				TITLE_SCREEN, ROUND_SCREEN, END_SCREEN
			};
	
			struct ScoreEntry {
				std::string name;
				uint32_t    score;
			};
	
			Game();

			void Run();

			void RecordScore();
			void ResetScore();
			uint32_t GetScore() const;
	
			void SortRanking();
			std::vector<ScoreEntry>& GetRanking();
	
			//TODO needed anymore?
			uint8_t GetCredits() const;
	
			RenderManager& GetRenderManager();
			InputManager&  GetInputManager();
			
		private:
			State    mState;
			uint8_t  mCredits;
			uint8_t  mRound;
			uint8_t  mFinalRound;
			uint32_t mScore;
			std::vector<ScoreEntry> mRanking;
			
			//TODO ResourceManager
			//TODO AudioManager
			InputManager         mInputManager;
			InputManager::Input  mInput;
			RenderManager        mRenderManager;
			sf::Time             mDeltaTime;
			std::shared_ptr<TitleScreenView> mTitleScreen;
			std::shared_ptr<RoundScreenView> mRoundScreen;
			std::shared_ptr<EndScreenView>   mEndScreenView;
			
			void SetNextRound();
			void GameOver();
			RoundScreenView::RoundUpdate WrapRoundUpdate();
			TitleScreenView::TitleUpdate WrapTitleUpdate();
		};

}

