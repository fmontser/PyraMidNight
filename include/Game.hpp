// Game state machine
#pragma once
#include <cstdint>
#include "TitleScreenView.hpp"
#include "RoundScreenView.hpp"
#include "InputManager.hpp"
#include "RenderManager.hpp"
#include "EndScreenView.hpp"


class Game {
	public:
		enum class State {
			TITLE_SCREEN, ROUND_SCREEN, END_SCREEN
		};

		struct ScoreEntry {
			std::string name;
			uint32_t    score;
		};

		Game();

		void Run();
		//TODO not IOC!!!!!
		void AddScore(uint32_t points);
		void ResetScore();
		void RecordScore();
		uint32_t GetScore() const;

		void SortRanking();
		std::vector<ScoreEntry>& GetRanking();
		
		//TODO not IOC!!!!!
		void AddCredit();
		void ConsumeCredit();
		uint8_t GetCredits() const;

		RenderManager& GetRenderManager();
		InputManager&  GetInputManager();
		
	private:
		State    mState;
		uint8_t  mCredits;
		uint8_t  mRound;
		uint8_t  mFinalRound;
		uint32_t mScore;
		std::vector<ScoreEntry> mRanking;
		
		RenderManager    mRenderManager;
		InputManager     mInputManager;
		TitleScreenView  mTitleScreen;
		RoundScreenView  mRoundScreen;
		EndScreenView    mEndScreenView;
		
		void SetNextRound();
		void GameOver();
	};