#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"

namespace pyramidnight {

	class Ball : public sf::Sprite {
	public:
		enum class State {
			DOCKED, PLAYING
		};

		Ball(const sf::Texture& texture);

		void Launch();
		void ResetPos(const sf::Vector2f& bumperPos);
		void Update(const sf::Vector2f &bumperPos, const sf::Time& deltaTime);
		void Bounce(const sf::Sprite &obj);
		void ApplyBumperMod(const sf::Sprite& bumper);

		std::optional<sf::Vector2f> GetCollisionPoint(const sf::FloatRect &rect);

		float GetBallDistance(const sf::Sprite &obj) const;
		const State& GetState() const;
		float GetRadius() const;
		
	private:
		State           mState;
		float           mSpeed;
		sf::Vector2f    mDirection;
		float           mRadius;
		float           mDistance;
		
		void  Move(const sf::Time& deltaTime);
		void  ResolveOverlap();
	};

}


