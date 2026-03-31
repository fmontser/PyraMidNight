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

namespace fknd {

	class Game {
		public:
			enum class State {
				MENU, TITLE_SCREEN, ROUND_SCREEN, END_SCREEN
			};
		
			Game();

			void Run();

		private:
			sf::RenderWindow& mWindow;
			State    mState;
			State    mPrevState;
			uint8_t  mCredits;
			uint8_t  mRound;
			uint8_t  mFinalRound;
			uint32_t mScore;
			std::shared_ptr<ResourceManager::SaveData> mSaveData;
			
			InputManager         mInputManager;
			InputManager::Input  mInput;
			RenderManager        mRenderManager;
			sf::Time             mDeltaTime;
			std::shared_ptr<MenuScreenView>  mMenuScreen;
			std::shared_ptr<TitleScreenView> mTitleScreen;
			std::shared_ptr<RoundScreenView> mRoundScreen;
			std::shared_ptr<EndScreenView>   mEndScreenView;
			
			void SetNextRound();
			void GameOver();
			void RecordScore();
			void ResetScore();
			void ResetCredits();
			void SortRanking();
			void Pause();
			void Resume();
			
			MenuScreenView::MenuScreenUpdate     WrapMenuScreenUpdate();
			TitleScreenView::TitleScreenUpdate   WrapTitleScreenUpdate();
			RoundScreenView::RoundScreenUpdate   WrapRoundScreenUpdate();
			EndScreenView::EndScreenUpdate       WrapEndScreenUpdate();
		};

}

