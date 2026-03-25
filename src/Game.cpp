#include "Game.hpp"
#include <limits>

constexpr uint32_t MAX_SCORE = std::numeric_limits<uint32_t>::max();
constexpr uint32_t MAX_CREDITS = std::numeric_limits<uint8_t>::max();

//TODO remove hardcoded final round value ¿?
Game::Game() :
	mState(Game::State::TITLE_SCREEN),
	mCredits(0),
	mRound(0),
	mFinalRound(3),
	mScore(0) {}

void Game::Update() {
	//TODO
	switch (mState) {
		case Game::State::TITLE_SCREEN:
			//TODO run or update SCREEN
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
