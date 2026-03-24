// Game state machine
#pragma once
#include <cstdint>

class Game {
	public:
		enum class State {
			TITLE_SCREEN, ROUND_SCREEN, END_SCREEN
		};

		void Update();

	private:
		State    mState;
		uint8_t  mCredits;
		uint8_t  mRound;
		uint8_t  mFinalRound;
		uint32_t mScore;

		void     ResetScore();
		void     SetNextRound();
		void     AddScore(uint32_t points);
		void     AddCredit();
		void     ConsumeCredit();
};