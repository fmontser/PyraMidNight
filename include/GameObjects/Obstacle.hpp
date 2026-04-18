#pragma once
#include <SFML/Graphics.hpp>
#include "ICollidable.hpp"
#include "Common.hpp"

namespace pyramidnight {

	class Obstacle : 
		public sf::Sprite, public ICollidable {
			public:
				Obstacle(const sf::Texture& texture);
			
				Info OnCollision(ICollidable& collider) override;
				std::optional<sf::Vector2f> GetCollisionPoint(const sf::FloatRect &rect) override;
	};
}