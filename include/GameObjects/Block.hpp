#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"

namespace fknd {

	class Block : public sf::Sprite {
		public:
			Block(const sf::Texture& texture, int8_t hitPoints);
		
			void Update(const sf::Time& deltaTime);
			bool Damage();
			int32_t GetScore() const;

		private:
			int8_t    mHitPoints;
			int32_t   mScorePoints;
			sf::Color mTint;
			float     mFlashTimer;
	};
}