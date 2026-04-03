#include "Block.hpp"
#include "AudioManager.hpp"

namespace pyramidnight {

	Block::Block(const sf::Texture& texture, int8_t hitPoints) : sf::Sprite(texture) {
		mHitPoints = hitPoints;
		mScorePoints = SCORE_BLOCK_MOD * mHitPoints;
		mFlashTimer = 0.0f;
		if (hitPoints == 2)
			setColor({255, 128, 64 , 255});
		else if (hitPoints == 3)
			setColor({64, 128, 255 , 255});
		mTint = getColor();
	}

	void Block::Update(const sf::Time& deltaTime) {
		if (mFlashTimer > 0.0f) {
			mFlashTimer -= deltaTime.asSeconds();
			setColor(sf::Color(sf::Color::White)); 
		} 
		else {
			setColor(mTint);
		}
	}

	bool Block::Damage()
	{
		float randomValue = BLOCK_ROT_MIN + static_cast<float>(rand())
						/ (static_cast<float>(RAND_MAX) / BLOCK_ROT_MAX);
		mHitPoints--;
		if (mHitPoints == 0) {
			AudioManager::Play(PATH_AUD_BLOCK_DESTROY, VOL_AUD_BLOCK_DESTROY, false);
			return true;
		}
		AudioManager::Play(PATH_AUD_BLOCK_DAMAGE, VOL_AUD_BLOCK_DAMAGE, false);
		mFlashTimer = BLOCK_FLASH_TIME;
		setRotation(sf::degrees(randomValue));
		return false;
	}

	int32_t Block::GetScore() const { return mScorePoints; }
}