#include "Game.hpp"
#include <limits>

constexpr uint32_t MAX_SCORE = std::numeric_limits<uint32_t>::max();
constexpr uint32_t MAX_CREDITS = std::numeric_limits<uint8_t>::max();

//TODO remove hardcoded values
Game::Game() :
	mWindow(sf::VideoMode(640, 896), "FranKanoid"),
	mTitleScreen(TitleScreenView(mWindow, mDeltaTime)),
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

//TODO to class
void drawFrame(sf::RenderWindow& window) {
	window.display();
}

void Game::Run() {

	mTitleScreen.Show();
	// Main loop
	while (mWindow.isOpen()) {
		mDeltaTime = mClock.restart();
		mWindow.clear();

		fetchInput(mWindow);

		mTitleScreen.Draw();

		drawFrame(mWindow);
	}


/* 	//TODO
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
	} */
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
