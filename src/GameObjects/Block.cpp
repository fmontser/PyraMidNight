#include "Block.hpp"
#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include "RenderManager.hpp"
#include "Ball.hpp"
#include "Flash.hpp"

namespace pyramidnight {

	Block::Block(const sf::Texture& texture, int8_t hitPoints) : sf::Sprite(texture) {
		CollidableType = ICollidable::Type::BLOCK;
		IsDynamic = true;
		mHitPoints = hitPoints;
		mScorePoints = mHitPoints * SCORE_BLOCK_MOD;
		
		// color for hitpoints
		if (hitPoints == 2)
			setColor({255, 128, 64 , 255});
		else if (hitPoints == 3)
			setColor({64, 128, 255 , 255});
		mTint = getColor();
	}

	ICollidable::Info Block::OnCollision(ICollidable &collider) {
		switch (collider.CollidableType) {
			case ICollidable::Type::BALL: return OnBallCollision(collider);
			default: break;
		}
		return { CollidableType, false, 0, std::nullopt };
	}

	std::optional<sf::Vector2f> Block::GetCollisionPoint(const sf::FloatRect &rect) {
		if (auto overlap = getGlobalBounds().findIntersection(rect))
			return overlap->position + (overlap->size / 2.0f);
		return std::nullopt;
	}

	ICollidable::Info Block::OnBallCollision(ICollidable &collider) {
		auto& ball = static_cast<Ball&>(collider);
		auto cpos = GetCollisionPoint(ball.getGlobalBounds());
		if (cpos != std::nullopt) {
			Damage();
			return { CollidableType, (mHitPoints == 0), static_cast<float>(mScorePoints), cpos };
		}
		return { CollidableType, false, 0, std::nullopt };
	}

	void Block::Damage() {
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
}