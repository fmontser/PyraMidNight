#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include "ICollidable.hpp"
#include "Common.hpp"
#include "Misile.hpp"

namespace pyramidnight {

	class Bumper : public sf::Sprite , public ICollidable, public std::enable_shared_from_this<Bumper> {
		public:
			struct BumperUpdate {
				bool holdLeft;
				bool holdRight;
				bool action;
				bool fine;
				bool coarse;
				sf::Time &deltaTime;
				std::vector<std::shared_ptr<sf::Drawable>>& drawables;
				std::vector<std::shared_ptr<Misile>>&       mMisileVector;
			};

			Bumper(const sf::Texture& texture, const sf::Texture& magicTexture);

			Info OnCollision(ICollidable& collider) override;
			std::optional<sf::Vector2f> GetCollisionPoint(const sf::FloatRect &rect);
			void Update(BumperUpdate update);
			void Move(BumperUpdate update);
			void EnablePenaltyFlashEffect(float duration);
			void EnableMagic(float duration);
			void FireMagic(bool action, const sf::Time& deltaTime,
					std::vector<std::shared_ptr<Misile>>& misiles,
					std::vector<std::shared_ptr<sf::Drawable>>& drawables);

			void SetSpeedPenalty(float speed);

		private:
			float              mSpeed;
			float              mSpeedPenalty;
			float              mIsMagicEnabled;
			float              mMagicDuration;
			float              mMagicFireRate;
			const sf::Texture& mMagicTexture;

			sf::Vector2f GetBumperFirePosition();
			void AnimateFrame(sf::Sprite &sprite, const sf::Time &deltaTime);

			float         mAnimationDelta;
			sf::IntRect   mAnimationRect;
	};

}
