#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"

namespace pyramidnight {

	class Block : public sf::Sprite, public std::enable_shared_from_this<Block> {
		public:
			Block(const sf::Texture& texture, int8_t hitPoints);
		
			void Update(const sf::Time& deltaTime); //TODO delete?
			bool Damage();
			int32_t GetScore() const;

		private:
			int8_t    mHitPoints;
			int32_t   mScorePoints;
			sf::Color mTint;
	};
}