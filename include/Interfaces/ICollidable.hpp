#pragma once
#include <SFML/System/Vector2.hpp>
#include <optional>
#include <cinttypes>

namespace pyramidnight {

	class ICollidable {
		public:

			virtual ~ICollidable() = default;

			enum class CollidableType {
				BALL, BLOCK, WALL, BUMPER, POWER_UP
			};

			struct Info {
				CollidableType              type = CollidableType::BALL;
				bool                        destroyed = false;
				int32_t                     scoreMod = 0;
				std::optional<sf::Vector2f> collisionPoint = std::nullopt;
			};

			virtual Info OnCollision(ICollidable& collider) = 0;

			CollidableType CollidableType;
	};
}