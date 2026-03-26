#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class RoundScreenView;

class Round {
	public:
		Round(RoundScreenView& screenView);

	private:
		RoundScreenView& mScreenView;
		std::shared_ptr<sf::RectangleShape> mPlayArea;

};