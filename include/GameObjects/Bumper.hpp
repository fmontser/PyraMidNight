#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"

namespace fknd {

	class Bumper : public sf::Sprite {
		public:
			Bumper(const sf::Texture& texture);

			void Move(int8_t magnitude, sf::Time &deltaTime, bool fine, bool coarse);
	
		private:
			float mSpeed;
	};

}
