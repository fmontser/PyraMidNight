#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Bumper.hpp"

class RoundScreenView;

class Round {
	public:
		Round(RoundScreenView& screenView);

	private:
		RoundScreenView& mScreenView;
		std::shared_ptr<sf::RectangleShape> mPlayArea;
		std::shared_ptr<sf::RectangleShape> mDeathArea;

		std::shared_ptr<sf::Texture> mBumperTex;
		std::shared_ptr<Bumper>      mBumper;
};