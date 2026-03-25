#include <limits>
#include "Game.hpp"
#include "RenderManager.hpp"

constexpr uint32_t MAX_SCORE = std::numeric_limits<uint32_t>::max();
constexpr uint32_t MAX_CREDITS = std::numeric_limits<uint8_t>::max();

//TODO remove hardcoded values
Game::Game() :
	mState(Game::State::TITLE_SCREEN),
	mCredits(0),
	mRound(0),
	mFinalRound(3),
	mScore(0),
	mRenderManager(),
	mInputManager(mRenderManager.GetWindow()) {}

void Game::Run() {


	//TODO set FPS LIMIT!!
	// main loop
	while (mRenderManager.GetWindow().isOpen()) {

		const auto& frameInput = mInputManager.FetchInput();
		const auto& deltaTime = mRenderManager.GetDeltaTime();

		if (frameInput.close)
			mRenderManager.GetWindow().close();	//TODO check resources/leaks

		switch (mState) {
			case Game::State::TITLE_SCREEN:
				//TODO .show() vestigial?
				mTitleScreen.Show();
				mTitleScreen.ProcessInput();
				mRenderManager.RenderFrame(mTitleScreen);
				break;
			case Game::State::ROUND_SCREEN:
				//TODO run or update SCREEN
				break;
			case Game::State::END_SCREEN:
				//TODO run or update SCREEN
				break;
			default:
				break;
		}
	}
}

void Game::SetNextRound() { 
	if (mRound < mFinalRound)
		mRound++;
}

void Game::AddScore(uint32_t points) {
	if (points > (MAX_SCORE - mScore))
		mScore = MAX_SCORE;
	else
		mScore += points;
}

void Game::ResetScore() { mScore = 0; }

void Game::AddCredit() {
	if (mCredits < MAX_CREDITS)
		mCredits++;
}

void Game::ConsumeCredit() {
	if (mCredits > 0)
		mCredits--;
}
