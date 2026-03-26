// Game state machine
#pragma once
#include <cstdint>
#include "TitleScreenView.hpp"
#include "InputManager.hpp"
#include "RenderManager.hpp"


class Game {
	public:
		enum class State {
			TITLE_SCREEN, ROUND_SCREEN, END_SCREEN
		};

		Game();

		void Run();
		void AddScore(uint32_t points);
		void ResetScore();
		void AddCredit();
		void ConsumeCredit();
		
		void SetNextRound();
		RenderManager& GetRenderManager();
		InputManager&  GetInputManager();

	private:
		State    mState;
		uint8_t  mCredits;
		uint8_t  mRound;
		uint8_t  mFinalRound;
		uint32_t mScore;

		RenderManager    mRenderManager;
		InputManager     mInputManager;
		TitleScreenView  mTitleScreen;

};