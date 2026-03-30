#include <limits>
#include <algorithm>
#include "Game.hpp"

namespace fknd {
	
	Game::Game() : mRenderManager(), mInputManager(mRenderManager.GetWindow()) {
		mState = Game::State::TITLE_SCREEN;
		mCredits = 0;
		mRound = 0;
		mFinalRound = GAME_FINAL_ROUND_ID; //TODO calculate from available levels or difficulty setting
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

		//TODO LEVEL VALIDATION exception!!
	}
	
	// main loop
	void Game::Run() {
	
		while (mRenderManager.GetWindow().isOpen()) {
			mInput = mInputManager.FetchInput();
			mDeltaTime = mRenderManager.GetDeltaTime();

			if (mInput.close)
				mRenderManager.GetWindow().close();

			switch (mState) {
				case Game::State::TITLE_SCREEN:
					if (mTitleScreen == nullptr)
						mTitleScreen = std::make_shared<TitleScreenView>();
					if (!mTitleScreen->Update(WrapTitleScreenUpdate())) {
						mState = State::ROUND_SCREEN;
						mTitleScreen = nullptr;
						break;
					}
					mRenderManager.RenderFrame(mTitleScreen->GetDrawables());
					break;
				case Game::State::ROUND_SCREEN:
					if (mRoundScreen == nullptr)
						mRoundScreen = std::make_shared<RoundScreenView>();
					if (!mRoundScreen->Update(WrapRoundScreenUpdate())) {
						mRoundScreen = nullptr;
						SetNextRound();
						break;
					}
					mRenderManager.RenderFrame(mRoundScreen->GetDrawables());
					break;
				case Game::State::END_SCREEN:
					if (mEndScreenView == nullptr)
						mEndScreenView = std::make_shared<EndScreenView>();
					if (!mEndScreenView->Update(WrapEndScreenUpdate())) {
						mState = State::TITLE_SCREEN;
						mEndScreenView = nullptr;
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
		if (mRound < mFinalRound) {
			mRound++;
			mRoundScreen = std::make_shared<RoundScreenView>();
		}
		else
			GameOver();
	}
	
	void Game::GameOver() {
		mState = State::END_SCREEN;
		RecordScore();
		ResetScore();
	}

	void Game::RecordScore() {
		mRanking.push_back({"   ", mScore});
		SortRanking();
		if (mRanking.size() > GAME_RANK_SIZE)
			mRanking.pop_back();
	}

	void Game::ResetScore() { mScore = 0; }
	
	void Game::SortRanking() {
		std::sort(mRanking.begin(), mRanking.end(),
		[](const EndScreenView::ScoreEntry& a, const EndScreenView::ScoreEntry& b) {
			return a.score > b.score;
		}
		);
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
			mRanking
		};
	}
}