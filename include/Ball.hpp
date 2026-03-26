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
		void Update(sf::Time& deltaTime);
		void Bounce(sf::Rect<float> rect);

		const State& GetState() const;
		const sf::Vector2f& GetPostion() const;
		const float GetRadius() const;

		void SetDirection(sf::Vector2f direction);
		
		private:
			State           mState;
			float           mSpeed;
			sf::Vector2f    mDirection;
			float           mRadius;
		
		void Move(sf::Time& deltaTime);
	};