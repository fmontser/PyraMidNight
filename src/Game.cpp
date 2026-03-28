#include <limits>
#include "Game.hpp"

constexpr uint32_t MAX_SCORE = std::numeric_limits<uint32_t>::max();
constexpr uint32_t MAX_CREDITS = std::numeric_limits<uint8_t>::max();

//TODO remove hardcoded values
Game::Game() :
	mState(Game::State::TITLE_SCREEN),
	mCredits(0),
	mRound(1),
	mFinalRound(1),
	mScore(0),
	mRenderManager(),
	mInputManager(mRenderManager.GetWindow()) {}

void Game::Run() {

	//TODO remove screens when moving forward!
	// main loop
	while (mRenderManager.GetWindow().isOpen()) {

		switch (mState) {
			case Game::State::TITLE_SCREEN:
				mTitleScreen.Update(*this);
				mRenderManager.RenderFrame(mTitleScreen);
				break;
			case Game::State::ROUND_SCREEN:
				mRoundScreen.Update(*this);
				mRenderManager.RenderFrame(mRoundScreen);
				break;
			case Game::State::END_SCREEN:
				//TODO run or update SCREEN
				//TODO title screen placeholder, remove

				mTitleScreen.Update(*this);
				mRenderManager.RenderFrame(mTitleScreen);
				break;
			default:
				break;
		}
	}
}

void Game::AddScore(uint32_t points) {
	if (points > (MAX_SCORE - mScore))
		mScore = MAX_SCORE;
	else
		mScore += points;
}

void Game::ResetScore() { mScore = 0; }

uint32_t Game::GetScore() const { return mScore; }

void Game::AddCredit() {
	if (mCredits < MAX_CREDITS)
		mCredits++;
}

void Game::ConsumeCredit() {
	if (mCredits > 0)
		mCredits--;
}

uint8_t Game::GetCredits() const { return mCredits; }

void Game::SetState(State state) { mState = state; }

void Game::SetNextRound() {
	if (mRound < mFinalRound)
		mRound++;
	else
		GameOver();
}

void Game::GameOver() {
	//TODO endscreen
	mState = State::END_SCREEN;
}

RenderManager &Game::GetRenderManager() { return mRenderManager; }
InputManager &Game::GetInputManager() { return mInputManager; }