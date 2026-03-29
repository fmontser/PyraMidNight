#pragma once
#include <string>
#include <cstdint>
#include <SFML/Graphics.hpp>

namespace fkd {
	//Ball
	inline constexpr float BALL_INIT_SPEED = 0.6f;
	inline constexpr sf::Vector2f BALL_INIT_DIR = {-1, -1};
	inline constexpr sf::Vector2f BALL_INIT_POS = {256, 832};
	inline constexpr sf::Vector2f BALL_DOCKED_OFFSET = {64, -18};


}