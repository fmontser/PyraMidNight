#pragma once

#include <SFML/Graphics.hpp>

namespace pyramidnight {

	class ISpawnable {
		public:
			virtual ~ISpawnable() = default;

			virtual void Spawn(const sf::Vector2f& position) = 0;
	};
}