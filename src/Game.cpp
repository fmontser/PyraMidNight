#include "Game.hpp"
#include <limits>
#include <RenderManager.hpp>

constexpr uint32_t MAX_SCORE = std::numeric_limits<uint32_t>::max();
constexpr uint32_t MAX_CREDITS = std::numeric_limits<uint8_t>::max();

//TODO remove hardcoded values
Game::Game() :
	mState(Game::State::TITLE_SCREEN),
	mCredits(0),
	mRound(0),
	mFinalRound(3),
	mScore(0) {}

//TODO to class
void fetchInput(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Game::Run() {
	//TODO delete hardcoded values
	RenderManager renderManager(640,896);
	sf::RenderWindow& window = renderManager.GetWindow();
	
	// main loop
	while (window.isOpen()) {

		fetchInput(window);

		switch (mState) {
			case Game::State::TITLE_SCREEN:
				mTitleScreen.Show();
				renderManager.RenderFrame(mTitleScreen);
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
