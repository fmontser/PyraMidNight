#pragma once
#include <optional>
#include <SFML/System/Vector2.hpp>

namespace pyramidnight {
	class ICollidable {
		public:

			virtual ~ICollidable() = default;

			struct Info {
				bool                        destroyed = false;
				int32_t                     scoreMod = false;
				std::optional<sf::Vector2f> collisionPos = {};
			};

			virtual std::optional<Info> OnCollision(ICollidable& collider) = 0;
/* 
			static std::optional<sf::Vector2f> GetCollisionPoint(
				const sf::FloatRect& rect0, const sf::FloatRect& rect1, float& distance);
				
			static std::optional<sf::Vector2f> GetCollisionPoint(
				sf::Vector2f center0, float radius0, sf::Vector2f center1, float radius1, float& distance);

			static std::optional<sf::Vector2f> GetCollisionPoint(
				const sf::FloatRect& rect, sf::Vector2f center, float radius, float& distance); */
	};
}