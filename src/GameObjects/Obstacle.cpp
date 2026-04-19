#include "Obstacle.hpp"
#include "Ball.hpp"

namespace pyramidnight {

	Obstacle::Obstacle(const sf::Texture &texture) : sf::Sprite(texture) {
		CollidableType = ICollidable::Type::OBSTACLE;
		IsDynamic = false;
	}

	ICollidable::Info Obstacle::OnCollision(ICollidable &collider) {
		(void)collider;
		return { CollidableType, false, 0, std::nullopt };
	}

	std::optional<sf::Vector2f> Obstacle::GetCollisionPoint(const sf::FloatRect &rect) {
		if (auto overlap = getGlobalBounds().findIntersection(rect))
			return overlap->position + (overlap->size / 2.0f);
		return std::nullopt;
	}
}
