#include "Block.hpp"

namespace fknd {

	Block::Block(const sf::Texture& texture, int8_t hitPoints) : sf::Sprite(texture) {
		mHitPoints = hitPoints;
		mScorePoints = SCORE_BLOCK_MOD * mHitPoints;
	}
	
	bool Block::Damage() {
		mHitPoints--;
		if (mHitPoints == 0)
			return true;
		return false;
	}

	int32_t Block::GetScore() { return mScorePoints; }
}