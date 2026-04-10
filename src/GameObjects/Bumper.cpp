#include <algorithm>
#include <cmath>
#include "Bumper.hpp"
#include "Ball.hpp"

namespace pyramidnight {
	
	Bumper::Bumper(const sf::Texture& texture) : sf::Sprite(texture) {
		mSpeed = BMPR_INIT_SPEED;
	}

	ICollidable::Info Bumper::OnCollision(ICollidable &collider) { 
		if (collider.CollidableType == CollidableType::BALL) {
			auto& ball = static_cast<Ball&>(collider);
			auto cpos = ball.GetCollisionPoint(getGlobalBounds());
			if (cpos != std::nullopt) {
				ball.Bounce(*this);
				ball.ApplyBumperMod(*this);
			}
		}
		return {CollidableType, false, 0, std::nullopt };
	}

	std::optional<sf::Vector2f> Bumper::GetCollisionPoint(const sf::FloatRect &rect) {
		if (auto overlap = getGlobalBounds().findIntersection(rect))
			return overlap->position + (overlap->size / 2.0f);
		return std::nullopt;
	}

	void Bumper::Move(int8_t magnitude, sf::Time &deltaTime, bool fine, bool coarse)
	{
		sf::Vector2 position = this->getPosition();
		if (fine && !coarse)
			mSpeed *= BMPR_FINE_SPEED_MOD;
		else if (!fine && coarse)
			mSpeed *= BMPR_COARSE_SPEED_MOD;

		position.x += magnitude * mSpeed * deltaTime.asMilliseconds();
		position.x = std::clamp(position.x, BMPR_MV_LIMIT_L, BMPR_MV_LIMIT_R);
		this->setPosition(position);
		mSpeed = BMPR_INIT_SPEED;
	}
}