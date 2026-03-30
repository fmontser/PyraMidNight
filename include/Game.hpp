// Game state machine
#pragma once
#include <cstdint>
#include "TitleScreenView.hpp"
#include "RoundScreenView.hpp"
#include "EndScreenView.hpp"
#include "RenderManager.hpp"
#include "ResourceManager.hpp"
#include "InputManager.hpp"
#include "Common.hpp"

namespace fknd {

	class Game {
		public:
			enum class State {
				TITLE_SCREEN, ROUND_SCREEN, END_SCREEN
			};
		
			Game();

			void Run();

		private:
			State    mState;
			uint8_t  mCredits;
			uint8_t  mRound;
			uint8_t  mFinalRound;
			uint32_t mScore;
			std::vector<EndScreenView::ScoreEntry> mRanking;
			
			//TODO ResourceManager
			//TODO AudioManager
			ResourceManager      mResourceManager;
			InputManager         mInputManager;
			InputManager::Input  mInput;
			RenderManager        mRenderManager;
			sf::Time             mDeltaTime;
			std::shared_ptr<TitleScreenView> mTitleScreen;
			std::shared_ptr<RoundScreenView> mRoundScreen;
			std::shared_ptr<EndScreenView>   mEndScreenView;
			

			void SetNextRound();
			void GameOver();
			void RecordScore();
			void ResetScore();
			void SortRanking();
			TitleScreenView::TitleScreenUpdate WrapTitleScreenUpdate();
			RoundScreenView::RoundScreenUpdate WrapRoundScreenUpdate();
			EndScreenView::EndScreenUpdate     WrapEndScreenUpdate();
		};

}

