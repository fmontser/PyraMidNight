#include "Misile.hpp"
#include "Common.hpp"
#include "RenderManager.hpp"

namespace pyramidnight {
	PowerUp::Misile(const sf::Texture& texture) : sf::Sprite(texture) {
		CollidableType = ICollidable::Type::MISILE;
		mIsSpawned = false;
		mIsDestroyed = false;
		mSpeed = 500.0f;
		mDirection = GAME_DIRECTION_UP;
	}
	
	void Misile::Spawn(
		const sf::Vector2f &position, std::vector<std::shared_ptr<sf::Drawable>>& drawables) {
		setPosition(position);
		drawables.push_back(shared_from_this());
		mIsSpawned = true;
	}

	void Misile::Update(const sf::Time& deltaTime) {
		if (mIsSpawned)
			ApplyMovement(deltaTime);
		DestroyIfOutside();
	}

	std::optional<sf::Vector2f> Misile::GetCollisionPoint(const sf::FloatRect &rect) {
		if (auto overlap = getGlobalBounds().findIntersection(rect))
			return overlap->position + (overlap->size / 2.0f);
		return std::nullopt;
	}

	void Misile::ApplyMovement(const sf::Time& deltaTime) {
		float movement = mDirection.y * mSpeed * deltaTime.asSeconds();
		move({0.0f, movement});
	}

	void Misile::DestroyIfOutside() {
		auto viewPort = RenderManager::GetWindow().getView().getViewport();
		if (viewPort.contains(getGlobalBounds().position))
			mIsDestroyed = true;
	}
}