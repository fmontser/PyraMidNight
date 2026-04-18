#pragma once
#include <optional>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace pyramidnight {

	class ICollidable {
		public:
			enum class Type {
				NONE, BALL, BLOCK, OBSTACLE, BUMPER, POWER_UP, MISILE
			};

			struct Info {
				Type                        type = Type::NONE;
				bool                        destroyed = false;
				float                       valueMod = 0.0f;
				std::optional<sf::Vector2f> collisionPoint = std::nullopt;
			};
			
			Type CollidableType = Type::NONE;
			bool IsDynamic = false;

			virtual ~ICollidable() = default;
			virtual Info OnCollision(ICollidable& collider) = 0;

		protected:
			virtual std::optional<sf::Vector2f> GetCollisionPoint(const sf::FloatRect &rect) = 0;
	};
}