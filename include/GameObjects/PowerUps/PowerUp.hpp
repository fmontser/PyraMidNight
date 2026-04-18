#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <optional>
#include "ICollidable.hpp"
#include "ISpawnable.hpp"

namespace pyramidnight {

	class PowerUp : 
		public sf::Sprite, public ICollidable,
		public ISpawnable, public std::enable_shared_from_this<PowerUp> {
			public:

				enum class Type {
					SCORE, CREDIT, GHOST, MAGIC
				};

				virtual ~PowerUp() = default;

				void Spawn(
					const sf::Vector2f& position,
					std::vector<std::shared_ptr<sf::Drawable>>& drawables) override;

				virtual void Update(const sf::Time &deltaTime);

				std::optional<sf::Vector2f> GetCollisionPoint(const sf::FloatRect &rect) override;

				PowerUp::Type  PowerUpType;

			protected:

				PowerUp(const sf::Texture& texture);
				PowerUp(const PowerUp& src) =  delete;
				PowerUp& operator=(const PowerUp& src) = delete;
				
				bool         mIsSpawned;
				bool         mIsDestroyed;
				float        mSpeed;
				sf::Vector2f mDirection;

				void ApplyGravity(const sf::Time &deltaTime);
				void DestroyIfOutside() override;
	};
}