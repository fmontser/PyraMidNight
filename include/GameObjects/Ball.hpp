#pragma once
#include <SFML/Graphics.hpp>
#include "ICollidable.hpp"
#include "Common.hpp"

namespace pyramidnight {

	class Ball : public sf::Sprite, public ICollidable, public std::enable_shared_from_this<Ball> {
	public:
		enum class State {
			DOCKED, PLAYING, DEAD
		};

		struct UpdateBall {
			bool                      action;
			const sf::Vector2f&       bumperPos;
			const sf::Time&           deltaTime;
			const sf::RectangleShape& deathArea;
			std::vector<std::shared_ptr<sf::Drawable>>& drawablesVector;
		};

		Ball(const sf::Texture& texture);

		State Update(UpdateBall update);
		Info OnCollision(ICollidable& collider) override;

	private:
		State           mState;
		float           mSpeed;
		sf::Vector2f    mDirection;
		float           mRadius;
		float           mDistance;
		bool            mIsTrailing;

		void Move(const sf::Time& deltaTime);
		void CheckDeath(const sf::RectangleShape &deathArea);
		void Launch(bool action);
		void Dock(const sf::Vector2f& bumperPos);
		void Bounce(const sf::Sprite &obj);
		void ApplyBumperMod(const sf::Sprite& bumper);
		void ResolveOverlap();
		ICollidable::Info OnBlockCollision(ICollidable &collider);
		ICollidable::Info OnObstacleCollision(ICollidable &collider);
		ICollidable::Info OnBumperCollision(ICollidable &collider);
		std::optional<sf::Vector2f> GetCollisionPoint(const sf::FloatRect &rect) override;

	};

}


