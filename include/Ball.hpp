#pragma once
#include <SFML/Graphics.hpp>

class Ball : public sf::Sprite {
	public:
		enum class State {
			DOCKED, PLAYING
		};

		Ball(const sf::Texture& texture);

		void Launch();
		void ResetPos(const sf::Vector2f& bumperPos);
		void Update(const sf::Vector2f &bumperPos, sf::Time& deltaTime);
		void Bounce(sf::Rect<float> rect, float distance);

		const State& GetState() const;
		const float GetRadius() const;

		void SetDirection(sf::Vector2f direction);
		
		private:
			State           mState;
			float           mSpeed;
			sf::Vector2f    mDirection;
			float           mRadius;
		
		void Move(sf::Time& deltaTime);
		float GetDistance(sf::Rect<float> rect);
		void ResolveOverlap(float distance);
	};