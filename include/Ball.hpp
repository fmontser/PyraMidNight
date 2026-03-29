#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"

namespace fknd {

	class Ball : public sf::Sprite {
	public:
		enum class State {
			DOCKED, PLAYING
		};

		Ball(const sf::Texture& texture);

		void Launch();
		void ResetPos(const sf::Vector2f& bumperPos);
		void Update(const sf::Vector2f &bumperPos, const sf::Time& deltaTime);
		void Bounce(const sf::Sprite &obj, float distance);
		void ApplyBumperMod(const sf::Sprite& bumper);

		const State& GetState() const;
		const float GetRadius() const;
		
	private:
		State           mState;
		float           mSpeed;
		sf::Vector2f    mDirection;
		float           mRadius;
		
		//TODO move GetBallDistance here?
		void  Move(const sf::Time& deltaTime);
		void  ResolveOverlap(float distance);
	};

}


