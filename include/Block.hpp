#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"

namespace fknd {

	//TODO more types of blocks...
	class Block : public sf::Sprite {
		public:
			Block(const sf::Texture& texture, int8_t hitPoints);
	
			bool Damage();
			int32_t GetScore();
		private:
			int8_t  mHitPoints;
			int32_t mScorePoints;
	};

}