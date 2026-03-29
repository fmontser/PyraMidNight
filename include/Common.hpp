#pragma once
#include <string>
#include <cstdint>
#include <SFML/Graphics.hpp>

namespace fknd {
	//Ball
	inline constexpr float BALL_INIT_SPEED = 0.6f;
	inline constexpr sf::Vector2f BALL_INIT_DIR = {-1, -1};
	inline constexpr sf::Vector2f BALL_INIT_POS = {256, 832};
	inline constexpr sf::Vector2f BALL_DOCKED_OFFSET = {64, -18};

	//Bumper
	inline constexpr float BMPR_INIT_SPEED = 0.45f;
	inline constexpr float BMPR_MV_LIMIT_L = 32.0f;
	inline constexpr float BMPR_MV_LIMIT_R = 480.0f;

	//Cursor
	inline constexpr float CUR_MV_OFFSET = 30.0f;
	inline constexpr float CUR_FONT_SZ = 48.0f;
	inline constexpr float CUR_OUTLINE_SZ = 2.0f;
	inline constexpr sf::Color CUR_OUTLINE_COL = sf::Color::Green;
	inline constexpr sf::Color CUR_FILL_COL = sf::Color::Transparent;

	//Level
	inline constexpr u_int8_t LVL_DIMENSIONS2 = 9;

}