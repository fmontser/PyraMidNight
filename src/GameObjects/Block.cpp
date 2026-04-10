#include "Block.hpp"
#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include "RenderManager.hpp"
#include "Ball.hpp"
#include "Flash.hpp"

namespace pyramidnight {

	Block::Block(const sf::Texture& texture, int8_t hitPoints) : sf::Sprite(texture) {
		mHitPoints = hitPoints;
		mScorePoints = mHitPoints * SCORE_BLOCK_MOD;
		CollidableType = ICollidable::Type::BLOCK;
		
		// color for hitpoints
		if (hitPoints == 2)
			setColor({255, 128, 64 , 255});
		else if (hitPoints == 3)
			setColor({64, 128, 255 , 255});
		mTint = getColor();
	}

	void Block::Damage()
	{
		float randomValue = 
			BLOCK_ROT_MIN + (rand() % static_cast<int>(BLOCK_ROT_MAX - BLOCK_ROT_MIN + 1));

		mHitPoints--;
		if (mHitPoints == 0) {
			auto sb = ResourceManager::GetAudio(PATH_AUD_BLOCK_DESTROY);
			AudioManager::Play({sb, VOL_AUD_BLOCK_DESTROY, PolySound::Type::SFX, false});
			return;
		}

		auto sb = ResourceManager::GetAudio(PATH_AUD_BLOCK_DAMAGE);
		AudioManager::Play({sb, VOL_AUD_BLOCK_DAMAGE, PolySound::Type::SFX, false});

		RenderManager::DisplayEffect(std::make_unique<Flash>(
			EFF_FLASH_BLK_TIME, EFF_FLASH_BLK_LAPSE, EFF_FLASH_BLK_COLOR, mTint, shared_from_this()));
		setRotation(sf::degrees(randomValue));
	}

	ICollidable::Info Block::OnCollision(ICollidable &collider) {
		if (collider.CollidableType == ICollidable::Type::BALL) {
			auto& ball = static_cast<Ball&>(collider);
			auto cpos = ball.GetCollisionPoint(getGlobalBounds());
			if (cpos != std::nullopt) {
				ball.Bounce(*this);
				Damage();
				return { CollidableType, (mHitPoints == 0), mScorePoints, cpos };
			}
		}
		return { CollidableType, false, 0, std::nullopt };
	}
}