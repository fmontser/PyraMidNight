#pragma once
#include "PowerUp.hpp"
#include <functional>

namespace pyramidnight {

	class ExtraScore : public PowerUp {
		public:
			ExtraScore(
				const sf::Texture& texture,
				std::function<void(uint8_t& score, uint32_t scoreMod)> addScore);

			void Apply(uint8_t &score);
				
		private:
			uint32_t mScoreMod;
			std::function<void(uint8_t& score, uint32_t scoreMod)> mAddScore;
	
	};
}