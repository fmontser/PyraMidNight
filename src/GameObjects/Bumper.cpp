#include <algorithm>
#include <cmath>
#include "Bumper.hpp"
#include "Ball.hpp"
#include "PowerUp.hpp"
#include "RenderManager.hpp"
#include "Flash.hpp"

namespace pyramidnight {
	
	Bumper::Bumper(const sf::Texture& texture) : sf::Sprite(texture) {
		mSpeed = BMPR_INIT_SPEED;
		mSpeedPenalty = 1.0f;
		mIsMagicEnabled = false;
		mMagicDuration = 0.0f;
		CollidableType = ICollidable::Type::BUMPER;
	}

	ICollidable::Info Bumper::OnCollision(ICollidable &collider) { 
		if (collider.CollidableType == ICollidable::Type::BALL) {
			auto& ball = static_cast<Ball&>(collider);
			auto cpos = ball.GetCollisionPoint(getGlobalBounds());
			if (cpos != std::nullopt) {
				ball.Bounce(*this);
				ball.ApplyBumperMod(*this);
			}
		}
		return { CollidableType, false, 0, std::nullopt };
	}

	std::optional<sf::Vector2f> Bumper::GetCollisionPoint(const sf::FloatRect &rect) {
		if (auto overlap = getGlobalBounds().findIntersection(rect))
			return overlap->position + (overlap->size / 2.0f);
		return std::nullopt;
	}

	void Bumper::Move(int8_t magnitude, sf::Time &deltaTime, bool fine, bool coarse) {
		sf::Vector2 position = this->getPosition();
		if (fine && !coarse)
			mSpeed *= BMPR_FINE_SPEED_MOD;
		else if (!fine && coarse)
			mSpeed *= BMPR_COARSE_SPEED_MOD;

		mSpeed *= mSpeedPenalty;
		position.x += magnitude * mSpeed * deltaTime.asSeconds();
		position.x = std::clamp(position.x, BMPR_MV_LIMIT_L, BMPR_MV_LIMIT_R);
		this->setPosition(position);
		mSpeed = BMPR_INIT_SPEED * mSpeedPenalty;
	}

	void Bumper::EnablePenaltyFlashEffect(float duration) {
		RenderManager::DisplayEffect(std::make_unique<Flash>(
			duration, EFF_FLASH_GHOST_LAPSE, EFF_FLASH_GHOST_ATTACK_COLOR, getColor(), shared_from_this()));
	}

	void Bumper::EnableMagic(float duration) {
		mIsMagicEnabled = true;
		mMagicDuration = std::abs(duration);
	}

	void Bumper::SetSpeedPenalty(float penalty) { mSpeedPenalty = penalty;	}
}