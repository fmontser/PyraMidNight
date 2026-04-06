// Game state machine
#pragma once
#include <cstdint>
#include "MenuScreenView.hpp"
#include "TitleScreenView.hpp"
#include "RoundScreenView.hpp"
#include "EndScreenView.hpp"
#include "ResourceManager.hpp"
#include "RenderManager.hpp"
#include "InputManager.hpp"
#include "Common.hpp"

namespace pyramidnight {

	class Game {
		public:
			enum class State {
				MENU, TITLE_SCREEN, ROUND_SCREEN, END_SCREEN
			};
		
			Game();

			void Run();

		private:
			State    mState;
			State    mPrevState;
			uint8_t  mCredits;
			uint8_t  mRound;
			uint8_t  mFinalRound;
			uint32_t mScore;
			
			InputManager::Input mInput;
			sf::RenderWindow&   mWindow;
			InputManager        mInputManager;
			sf::Time            mDeltaTime; //TODO elimnar, usar renderManager

			std::unique_ptr<MenuScreenView>  mMenuScreen;
			std::unique_ptr<TitleScreenView> mTitleScreen;
			std::unique_ptr<RoundScreenView> mRoundScreen;
			std::unique_ptr<EndScreenView>   mEndScreenView;
			
			void SetNextRound();
			void GameOver();
			void RecordScore();
			void ResetScore();
			void ResetCredits();
			void SortRanking();
			void Pause();
			void Resume();
			
			MenuScreenView::MenuScreenUpdate   WrapMenuScreenUpdate();
			TitleScreenView::TitleScreenUpdate WrapTitleScreenUpdate();
			RoundScreenView::RoundScreenUpdate WrapRoundScreenUpdate();
			EndScreenView::EndScreenUpdate     WrapEndScreenUpdate();
	};
}

