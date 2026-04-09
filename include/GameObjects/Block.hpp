#pragma once
#include <SFML/Graphics.hpp>
#include "ICollidable.hpp"
#include "Common.hpp"

namespace pyramidnight {

	class Block : 
		public sf::Sprite, public ICollidable, public std::enable_shared_from_this<Block> {
			public:
				Block(const sf::Texture& texture, int8_t hitPoints);

				Info OnCollision(ICollidable& collider) override;
				
			private:
				int8_t    mHitPoints;
				int32_t   mScorePoints;
				sf::Color mTint;

				void Damage();
	};
}