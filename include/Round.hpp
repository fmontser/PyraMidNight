#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Bumper.hpp"
#include "Ball.hpp"

class RoundScreenView;

class Round {
	public:
		Round(RoundScreenView& screenView);

		Bumper& GetBumper();
		Ball& GetBall();

	private:
		RoundScreenView& mScreenView;
		std::shared_ptr<sf::RectangleShape> mPlayArea;
		std::shared_ptr<sf::RectangleShape> mDeathArea;

		std::shared_ptr<sf::Texture> mBumperTex;
		std::shared_ptr<Bumper>      mBumper;
		std::shared_ptr<sf::Texture> mBallTex;
		std::shared_ptr<Ball>      mBall;
};