#pragma once
#include <SFML/Graphics.hpp>

class Ball : public sf::Sprite {
	public:
		enum class State {
			DOCKED, MOVING
		};

		Ball(const sf::Texture& texture);

		void Launch();
		void ResetPos(const sf::Vector2f& bumperPos);
		
	private:
		State        mState;
		float        mSpeed;
		sf::Vector2f mLaunchPos;

		void Move(int32_t magnitude, sf::Time& deltaTime);
	};