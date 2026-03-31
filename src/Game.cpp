#include <limits>
#include <algorithm>
#include "Game.hpp"
#include "AudioManager.hpp"

namespace fknd {
	
	Game::Game() : mRenderManager(), mInputManager(mRenderManager.GetWindow()) {
		ResourceManager::Init();
		mSaveData = std::make_shared<ResourceManager::SaveData>(ResourceManager::LoadUserData());
		AudioManager::Init();
		AudioManager::SetBgmVolume(mSaveData->bgmVol);
		AudioManager::SetSfxVolume(mSaveData->sfxVol);

		mState = State::TITLE_SCREEN;
		mCredits = 0;
		mRound = 0;
		mFinalRound = GAME_FINAL_ROUND_ID;
		mScore = 0;
	
		mTitleScreen = nullptr;
		mRoundScreen = nullptr;
		mEndScreenView = nullptr;
		SortRanking();
	}
	
	// main loop
	void Game::Run() {

		while (mRenderManager.GetWindow().isOpen()) {
			mInput = mInputManager.FetchInput();
			mDeltaTime = mRenderManager.GetDeltaTime();

			if (mInput.close)
				mRenderManager.GetWindow().close();
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
						ResourceManager::SaveUserData(*mSaveData);
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
						ResourceManager::SaveUserData(*mSaveData);
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
		RecordScore();
		ResetScore();
		ResetCredits();
	}

	void Game::RecordScore() {
		mSaveData->ranking.push_back({"   ", mScore});
		SortRanking();
		if (mSaveData->ranking.size() > GAME_RANK_SIZE)
			mSaveData->ranking.pop_back();
	}

	void Game::ResetScore() { mScore = 0; }

	void Game::ResetCredits() { mCredits = 0; }

	void Game::SortRanking() {
		std::sort(mSaveData->ranking.begin(), mSaveData->ranking.end(),
		[](const ResourceManager::ScoreEntry& a, const ResourceManager::ScoreEntry& b) {
			return a.score > b.score;
		}
		);
	}

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
				mInput.down,
				mSaveData
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
			mScore,
			mSaveData->ranking
		};
	}
}