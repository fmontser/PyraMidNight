#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <optional>
#include "ICollidable.hpp"
#include "ISpawnable.hpp"

namespace pyramidnight {

	class Misile : 
		public sf::Sprite, public ICollidable,
		public ISpawnable, public std::enable_shared_from_this<Misile> {
			public:

				enum class Type {
					HOLY_MISILE
				};

				virtual ~Misile() = default;

				void Spawn(
					const sf::Vector2f& position,
					std::vector<std::shared_ptr<sf::Drawable>>& drawables) override;

				virtual void Update(const sf::Time &deltaTime);

				std::optional<sf::Vector2f> GetCollisionPoint(const sf::FloatRect &rect);

				Misile::Type  MisileType;

			protected:

				Misile(const sf::Texture& texture);
				Misile(const Misile& src) =  delete;
				Misile& operator=(const Misile& src) = delete;
				
				bool         mIsSpawned;
				bool         mIsDestroyed;
				float        mSpeed;
				sf::Vector2f mDirection;

				void ApplyMovement(const sf::Time &deltaTime);
				void DestroyIfOutside() override;
	};
}