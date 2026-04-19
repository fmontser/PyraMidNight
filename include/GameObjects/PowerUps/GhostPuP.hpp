#pragma once
#include <functional>
#include <SFML/System/Angle.hpp>
#include "PowerUp.hpp"

namespace pyramidnight {

	class GhostPuP : public PowerUp {
		public:
			GhostPuP(const sf::Texture& texture);

			void Update(const sf::Time &deltaTime) override;
			ICollidable::Info OnCollision(ICollidable &collider);

			void Defeat();

		private:
			float         mBumperSpeedPenalty;
			float         mDiveTimer;
			float         mDiveLimit;
			float         mAnimationDelta;
			sf::IntRect   mAnimationRect;
			sf::IntRect   mSpriteRect;
			sf::Vector2u  mTextureSize;
			float         mDeltaX;
			float         mDeltaY;
			bool          mFlashEnabled;
			float         mAttackTimer;
			float         mAttackLimit;
			bool          mIsAttacking;
			bool          mIsDefeated;
			
			ICollidable::Info OnBumperCollision(ICollidable &collider);
			ICollidable::Info OnMisileCollision(ICollidable &collider);
			void ApplyGhostlyMovement(const sf::Time &deltaTime);
			void UpdateAttack(const sf::Time &deltaTime);
			void EnableFlashEffect();
			void EnableAttackFlashEffect();
			int GenerateDirection();
			float GenerateHoverTime();
			void AnimateFrame(const sf::Time &deltaTime);
			void MirrorSprite();
	};
}