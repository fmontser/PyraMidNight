#include <cmath>
#include "PowerUp.hpp"
#include "Common.hpp"
#include "RenderManager.hpp"

namespace pyramidnight {
	PowerUp::PowerUp(const sf::Texture& texture) : sf::Sprite(texture) {
		CollidableType = ICollidable::Type::POWER_UP;
		mIsSpawned = false;
		mIsDestroyed = false;
		mSpeed = 200.0f;
		mDirection = GAME_DIRECTION_DOWN;
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
		DestroyIfOutside();
	}

	std::optional<sf::Vector2f> PowerUp::GetCollisionPoint(const sf::FloatRect &rect) {
		if (auto overlap = getGlobalBounds().findIntersection(rect))
			return overlap->position + (overlap->size / 2.0f);
		return std::nullopt;
	}

	void PowerUp::ApplyGravity(const sf::Time& deltaTime) {
		float gravity = mDirection.y * GAME_GRAVITY * mSpeed * deltaTime.asSeconds();
		move({0.0f, gravity});
	}

	void PowerUp::DestroyIfOutside() {
		auto viewPort = RenderManager::GetWindow().getView().getViewport();
		if (viewPort.contains(getGlobalBounds().position))
			mIsDestroyed = true;
	}
}