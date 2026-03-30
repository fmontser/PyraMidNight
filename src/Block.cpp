#include "Block.hpp"
#include "AudioManager.hpp"

namespace fknd {

	Block::Block(const sf::Texture& texture, int8_t hitPoints) : sf::Sprite(texture) {
		mHitPoints = hitPoints;
		mScorePoints = SCORE_BLOCK_MOD * mHitPoints;
	}
	
	bool Block::Damage() {
		mHitPoints--;
		if (mHitPoints == 0) {
			AudioManager::Play(PATH_AUD_BLOCK_DESTROY, VOL_AUD_BLOCK_DESTROY, false);
			return true;
		}
		AudioManager::Play(PATH_AUD_BLOCK_DAMAGE, VOL_AUD_BLOCK_DAMAGE, false);
		return false;
	}

	int32_t Block::GetScore() { return mScorePoints; }
}