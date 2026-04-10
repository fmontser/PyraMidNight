#include "ExtraScore.hpp"

namespace pyramidnight {
	
	ExtraScore::ExtraScore(
		const sf::Texture &texture,
		std::function<void(uint8_t& score, uint32_t scoreMod)> addScore) : PowerUp(texture) {
			mAddScore = addScore;
	}

	void ExtraScore::Apply(uint8_t &score) {
		mAddScore(score, mScoreMod);
	}
}