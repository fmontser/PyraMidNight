#include <limits>
#include <algorithm>
#include "Game.hpp"

constexpr uint32_t MAX_SCORE = std::numeric_limits<uint32_t>::max();
constexpr uint32_t MAX_CREDITS = std::numeric_limits<uint8_t>::max();

//TODO remove hardcoded values
Game::Game() : mRenderManager(), mInputManager(mRenderManager.GetWindow()) {
	mState = Game::State::TITLE_SCREEN;
	mCredits = 0;
	mRound = 1;
	mFinalRound = 1; //TODO calculate from available levels or difficulty setting
	mScore = 0;

	//TODO make score persistent (when resourceMAnager is added)
	//Fake data
	mRanking.push_back({"RAA", 1000000});
	mRanking.push_back({"ELI", 900000});
	mRanking.push_back({"JMA", 800000});
	mRanking.push_back({"IOQ", 700000});
	mRanking.push_back({"FFF", 600000});
	mRanking.push_back({"ISS", 500000});
	mRanking.push_back({"YSS", 400000});
	mRanking.push_back({"PAS", 300000});
	mRanking.push_back({"TOI", 200000});
	mRanking.push_back({"CAN", 0});
	SortRanking();
}

void Game::Run() {

	//TODO remove screens when moving forward!
	//TODO proper memory management with screenViews!!!
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
				mEndScreenView.Update(*this);
				mRenderManager.RenderFrame(mEndScreenView);
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

void Game::RecordScore() {
	mRanking.push_back({"???", mScore});
	SortRanking();
	if (mRanking.size() > 10)
		mRanking.pop_back();
}

void Game::SortRanking() {
	std::sort(mRanking.begin(), mRanking.end(),
	[](const Game::ScoreEntry& a, const Game::ScoreEntry& b) {
		return a.score > b.score;
	}
	);
}

uint32_t Game::GetScore() const { return mScore; }
std::vector<Game::ScoreEntry> &Game::GetRanking() { return mRanking; }

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
	mState = State::END_SCREEN;
	RecordScore();
	ResetScore();
}

RenderManager &Game::GetRenderManager() { return mRenderManager; }
InputManager &Game::GetInputManager() { return mInputManager; }