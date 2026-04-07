// Game state machine
#pragma once
#include <cstdint>
#include "MenuScreenView.hpp"
#include "TitleScreenView.hpp"
#include "RoundScreenView.hpp"
#include "EndScreenView.hpp"
#include "InputManager.hpp"
#include "Common.hpp"

namespace pyramidnight {

	class Game {
		public:
			enum class State {
				MENU, TITLE_SCREEN, ROUND_SCREEN, END_SCREEN
			};
		
			Game();

			void Run(int testLevel);

		private:
			State               mState;
			State               mPrevState;
			uint8_t             mCredits;
			uint8_t             mRound;
			uint8_t             mFinalRound;
			uint32_t            mScore;
			InputManager::Input mInput;
			sf::Time            mDeltaTime;

			std::unique_ptr<MenuScreenView>  mMenuScreen;
			std::unique_ptr<TitleScreenView> mTitleScreen;
			std::unique_ptr<RoundScreenView> mRoundScreen;
			std::unique_ptr<EndScreenView>   mEndScreenView;
			
			void SetNextRound();
			void GameOver();
			void RecordScore();
			void ResetScore();
			void ResetCredits();
			
			// wrapers to update ScreeViews
			MenuScreenView::MenuScreenUpdate   WrapMenuScreenUpdate();
			TitleScreenView::TitleScreenUpdate WrapTitleScreenUpdate();
			RoundScreenView::RoundScreenUpdate WrapRoundScreenUpdate();
			EndScreenView::EndScreenUpdate     WrapEndScreenUpdate();
	};
}

