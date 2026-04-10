#pragma once
#include "ICollidable.hpp"
#include "ISpawnable.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace pyramidnight {

	class PowerUp : public sf::Sprite, public ICollidable, public ISpawnable{
		public:

			virtual ~PowerUp() = default;

			void Spawn(const sf::Vector2f& position) override;

		protected:

			PowerUp(const sf::Texture& texture);
			PowerUp(const PowerUp& src) =  delete;
			PowerUp& operator=(const PowerUp& src) = delete;

			float        mSpeed;
			sf::Vector2f mDirection;

			void ApplyGravity();
	};
}