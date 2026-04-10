#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

namespace pyramidnight {

	class ISpawnable {
		public:
			virtual ~ISpawnable() = default;

			virtual void Spawn(
				const sf::Vector2f& position,
				std::vector<std::shared_ptr<sf::Drawable>>& drawables) = 0;
	};
}