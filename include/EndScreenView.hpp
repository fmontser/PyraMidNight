#pragma once
#include "ScreenView.hpp"
#include <string>

class EndScreenView : public ScreenView {
	public:
		struct ScoreEntry {
			std::shared_ptr<sf::Text> name;
			std::shared_ptr<sf::Text> score;
		};

		EndScreenView();
		void Update(Game& game) override;

	private:
		std::shared_ptr<sf::Font> mFont;
		std::shared_ptr<sf::Text> mTitleTxt;
		std::shared_ptr<sf::Text> mStartTxt;
		std::shared_ptr<sf::Texture> mBackgroundTex;
		std::shared_ptr<sf::Sprite> mBackground;

		std::vector<ScoreEntry> mRankingTxt;

		void ShowRanking(Game& game);
		std::string PadZeroScore(uint32_t score, uint32_t digits);
};