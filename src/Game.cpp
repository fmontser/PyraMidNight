#include <limits>
#include <algorithm>
#include "Game.hpp"

namespace fknd {
	
	Game::Game() : mRenderManager(), mInputManager(mRenderManager.GetWindow()) {
		mState = Game::State::TITLE_SCREEN;
		mCredits = 0;
		mRound = 1;
		mFinalRound = 1; //TODO calculate from available levels or difficulty setting
		mScore = 0;
	
		mTitleScreen = nullptr;
		mRoundScreen = nullptr;
		mEndScreenView = nullptr;
	
		//TODO make score persistent (when resourceMAnager is added)
		//Fake data
		mRanking.push_back({"RAA", 1000000});
		mRanking.push_back({"ELI", 900000});
		mRanking.push_back({"JMA", 800000});
		mRanking.push_back({"IOQ", 700000});
		mRanking.push_back({"FFF", 600000});
		mRanking.push_back({"ISS", 3000});
		mRanking.push_back({"YSS", 1000});
		mRanking.push_back({"PAS", 500});
		mRanking.push_back({"TOI", 200});
		mRanking.push_back({"CAN", 1});
		SortRanking();
	}
	
	void Game::Run() {
	
		// main loop
		while (mRenderManager.GetWindow().isOpen()) {
			mInput = mInputManager.FetchInput();
			mDeltaTime = mRenderManager.GetDeltaTime();

			if (mInput.close)
				mRenderManager.GetWindow().close();

			switch (mState) {
				case Game::State::TITLE_SCREEN:
					if (mTitleScreen == nullptr)
						mTitleScreen = std::make_shared<TitleScreenView>();
					if (!mTitleScreen->Update(WrapTitleUpdate())) {
						mState = State::ROUND_SCREEN;
						mTitleScreen = nullptr;
						break;
					}
					mRenderManager.RenderFrame(*mTitleScreen);
					break;
				case Game::State::ROUND_SCREEN:
					if (mRoundScreen == nullptr)
						mRoundScreen = std::make_shared<RoundScreenView>();
					if (!mRoundScreen->Update(WrapRoundUpdate())) {
						//TODO load next level or gameOVer
						GameOver();
						mRoundScreen = nullptr;
						break;
					}
					mRenderManager.RenderFrame(*mRoundScreen);
					break;
				case Game::State::END_SCREEN:
					if (mEndScreenView == nullptr)
						mEndScreenView = std::make_shared<EndScreenView>();
					if (!mEndScreenView->Update(*this)) {
						mState = State::TITLE_SCREEN;
						mEndScreenView = nullptr;
						break;
					}
					mRenderManager.RenderFrame(*mEndScreenView);
					break;
				default:
					break;
			}
		}
	}
	
	void Game::RecordScore() {
		mRanking.push_back({"   ", mScore});
		SortRanking();
		if (mRanking.size() > GAME_RANK_SIZE)
		mRanking.pop_back();
	}
	void Game::ResetScore() { mScore = 0; }
	uint32_t Game::GetScore() const { return mScore; }
	
	void Game::SortRanking() {
		std::sort(mRanking.begin(), mRanking.end(),
		[](const Game::ScoreEntry& a, const Game::ScoreEntry& b) {
			return a.score > b.score;
		}
		);
	}
	
	std::vector<Game::ScoreEntry> &Game::GetRanking() { return mRanking; }
	
	//TODO needed anymore?
	uint8_t Game::GetCredits() const { return mCredits; }
	
	void Game::SetNextRound() {
		if (mRound < mFinalRound)
			mRound++;
		else
			GameOver();
	}
	
	void Game::GameOver() {
		mState = State::END_SCREEN;
		RecordScore();
		ResetScore();
	}

	RoundScreenView::RoundUpdate Game::WrapRoundUpdate() {
		return {
				mDeltaTime,
				mInput.holdLeft,
				mInput.holdRight,
				mInput.action,
				mCredits,
				mScore
				};
	}

	TitleScreenView::TitleUpdate Game::WrapTitleUpdate() {
		return {
				mInput.action,
				mInput.coin,
				mCredits
		};
	}

	RenderManager &Game::GetRenderManager() { return mRenderManager; }
	InputManager &Game::GetInputManager() { return mInputManager; }

}