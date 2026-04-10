#include <cmath>
#include "PowerUp.hpp"
#include "Common.hpp"

namespace pyramidnight {
	PowerUp::PowerUp(const sf::Texture& texture) : sf::Sprite(texture) {
		mIsSpawned = false;
		mSpeed = 1.0f;
		mDirection = GAME_DIRECTION_DOWN;
		CollidableType = ICollidable::Type::POWER_UP;
	}
	
	void PowerUp::Spawn(
		const sf::Vector2f &position, std::vector<std::shared_ptr<sf::Drawable>>& drawables) {
		setPosition(position);
		drawables.push_back(shared_from_this());
		mIsSpawned = true;
	}

	void PowerUp::Update(const sf::Time& deltaTime) {
		if (mIsSpawned)
			ApplyGravity(deltaTime);
	}

	void PowerUp::ApplyGravity(const sf::Time& deltaTime) {
		mDirection.y *= GAME_GRAVITY * mSpeed * deltaTime.asSeconds();
		float gravity = std::sqrtf((mDirection.y * mDirection.y) + (mSpeed * mSpeed));
		move({0.0f, gravity});
	}
}