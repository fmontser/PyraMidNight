#include <limits>
#include <algorithm>
#include "Game.hpp"
#include "UserDataManager.hpp"
#include "AudioManager.hpp"

#include <iostream>

namespace pyramidnight {
	
	Game::Game() : mRenderManager(), mWindow(mRenderManager.GetWindow()), mInputManager(mRenderManager.GetWindow()) {
		ResourceManager::Init();

		
		AudioManager::Init();
		AudioManager::SetBgmVolume(UserDataManager::GetUserData().bgmVol);
		AudioManager::SetSfxVolume(UserDataManager::GetUserData().sfxVol);

		mState = State::TITLE_SCREEN;
		mCredits = 0;
		mRound = 0;
		mFinalRound = GAME_FINAL_ROUND_ID;
		mScore = 0;
	
		mTitleScreen = nullptr;
		mRoundScreen = nullptr;
		mEndScreenView = nullptr;
	}
	
	// main loop
	void Game::Run() {
		while (mRenderManager.GetWindow().isOpen()) {
			AudioManager::Update();
			mInput = mInputManager.FetchInput();
			mDeltaTime = mRenderManager.GetDeltaTime();

			if (mInput.menu) {
				if (mState != State::MENU) {
					mPrevState = mState;
					mState = State::MENU;
					mInput.menu = false;
				}
			}
			
			switch (mState) {
				case State::MENU:
					if (mMenuScreen == nullptr) {
						Pause();
						mMenuScreen = std::make_shared<MenuScreenView>();
					}
					if (!mMenuScreen->Update(WrapMenuScreenUpdate())) {
						mState = mPrevState;
						mMenuScreen = nullptr;
						Resume();
						break;
					}
					mRenderManager.RenderFrame(mMenuScreen->GetDrawables());
					break;
				case State::TITLE_SCREEN:
					if (mTitleScreen == nullptr)
						mTitleScreen = std::make_shared<TitleScreenView>();
					if (!mTitleScreen->Update(WrapTitleScreenUpdate())) {
						mState = State::ROUND_SCREEN;
						mTitleScreen = nullptr;
						break;
					}
					mRenderManager.RenderFrame(mTitleScreen->GetDrawables());
					break;
				case State::ROUND_SCREEN:
					if (mRoundScreen == nullptr)
						mRoundScreen = std::make_shared<RoundScreenView>();
					if (!mRoundScreen->Update(WrapRoundScreenUpdate())) {
						mRoundScreen = nullptr;
						SetNextRound();
						break;
					}
					mRenderManager.RenderFrame(mRoundScreen->GetDrawables());
					break;
				case State::END_SCREEN:
					if (mEndScreenView == nullptr)
						mEndScreenView = std::make_shared<EndScreenView>();
					if (!mEndScreenView->Update(WrapEndScreenUpdate())) {
						mState = State::TITLE_SCREEN;
						mEndScreenView = nullptr;
						UserDataManager::SaveRanking();
						ResetScore();
						break;
					}
					mRenderManager.RenderFrame(mEndScreenView->GetDrawables());
					break;
					default:
					break;
				}
			}
		}
		
		void Game::SetNextRound() {
			if (mRound < mFinalRound && mCredits > 0) {
				mRound++;
				mRoundScreen = std::make_shared<RoundScreenView>();
			}
			else {
				mRound = 0;
				GameOver();
			}
		}
		
		void Game::GameOver() {
			mState = State::END_SCREEN;
			ResetCredits();
	}

	void Game::ResetScore() { mScore = 0; }

	void Game::ResetCredits() { mCredits = 0; }

	void Game::Pause() {
		if (mTitleScreen != nullptr)
			mTitleScreen->Pause();
		if (mRoundScreen != nullptr)
			mRoundScreen->Pause();
		if (mEndScreenView != nullptr)
			mEndScreenView->Pause();
	}

	void Game::Resume() {
		if (mTitleScreen != nullptr)
			mTitleScreen->Resume();
		if (mRoundScreen != nullptr)
			mRoundScreen->Resume();
		if (mEndScreenView != nullptr)
			mEndScreenView->Resume();
	}

	MenuScreenView::MenuScreenUpdate Game::WrapMenuScreenUpdate() {
		return {
				mInput.action,
				mInput.menu,
				mInput.left,
				mInput.right,
				mInput.up,
				mInput.down
		};
	}

	TitleScreenView::TitleScreenUpdate Game::WrapTitleScreenUpdate() {
		return {
				mInput.action,
				mInput.coin,
				mCredits
		};
	}

	RoundScreenView::RoundScreenUpdate Game::WrapRoundScreenUpdate() {
		return {
				mRound,
				mWindow,
				mDeltaTime,
				mInput.holdLeft,
				mInput.holdRight,
				mInput.coarse,
				mInput.fine,
				mInput.action,
				mCredits,
				mScore
				};
	}

	EndScreenView::EndScreenUpdate Game::WrapEndScreenUpdate() {
		return {
				mInput.left,
				mInput.right,
				mInput.up,
				mInput.down,
				mInput.action,
				mScore
		};
	}
}
