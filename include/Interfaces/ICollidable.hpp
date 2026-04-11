#pragma once
#include <SFML/System/Vector2.hpp>
#include <optional>
#include <cinttypes>

namespace pyramidnight {

	class ICollidable {
		public:

			virtual ~ICollidable() = default;

			enum class Type {
				BALL, BLOCK, OBSTACLE, BUMPER, POWER_UP
			};

			struct Info {
				Type                        type = Type::BALL;
				bool                        destroyed = false;
				float                     valueMod = 0.0f;
				std::optional<sf::Vector2f> collisionPoint = std::nullopt;
			};

			virtual Info OnCollision(ICollidable& collider) = 0;

			Type CollidableType;
	};
}