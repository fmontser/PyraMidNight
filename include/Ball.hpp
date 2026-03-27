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
		void Update(const sf::Vector2f &bumperPos,const sf::Time& deltaTime);
		void Bounce(const sf::Sprite &obj, float distance);

		const State& GetState() const;
		const float GetRadius() const;
		
	private:
		State           mState;
		float           mSpeed;
		sf::Vector2f    mDirection;
		float           mRadius;
		
		void Move(const sf::Time& deltaTime);
		float GetDistance(sf::Rect<float> rect);
		void ResolveOverlap(float distance);
	};