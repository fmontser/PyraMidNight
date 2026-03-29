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
	inline constexpr std::string_view CUR_CHAR_SET = " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	//TitleScreenView
		//Text
		inline constexpr sf::Color TITLE_TXT_FILLCOL = sf::Color::Blue;
		inline constexpr sf::Color TITLE_TXT_OUTCOL = sf::Color::Yellow;
		inline constexpr float TITLE_TXT_OUTLINE_SZ = 3.0f;
		inline constexpr uint32_t TITLE_TXT_CHAR_SZ = 90;
		inline constexpr uint32_t TITLE_TXT_CREDITS_CHAR_SZ = 48;
		inline constexpr uint32_t TITLE_TXT_START_CHAR_SZ = 40;
		inline constexpr std::string_view TITLE_STR = "FranKanoid";
		inline constexpr std::string_view TITLE_CREDITS_STR = "Insert coin! credits ";
		inline constexpr std::string_view TITLE_START_STR = "Press SPACE to start!";
		//Bg
		inline constexpr sf::Color TITLE_BG_TINT = sf::Color({255, 255, 255, 255});


	//RoundScreenView
		//Text
		inline constexpr sf::Color ROUND_TXT_FILLCOL = sf::Color::White;
		inline constexpr sf::Color ROUND_TXT_OUTCOL = sf::Color::Blue;
		inline constexpr float ROUND_TXT_OUTLINE_SZ = 1.0f;
		inline constexpr uint32_t ROUND_TXT_CHAR_SZ = 24;
		inline constexpr std::string_view ROUND_CREDITS_STR = "CREDITS ";
		inline constexpr std::string_view ROUND_SCORE_STR = "SCORE ";
		//Bg
		inline constexpr sf::Color ROUND_BG_TINT = sf::Color({0, 0, 255, 128});
		//Level
		inline constexpr u_int8_t LVL_DIMENSIONS2 = 9;

	//EndScreenView
		//Text
		inline constexpr sf::Color END_TXT_FILLCOL = sf::Color::Blue;
		inline constexpr sf::Color END_TXT_OUTCOL = sf::Color::Yellow;
		inline constexpr float END_TXT_OUTLINE_SZ = 4.0f;
		inline constexpr float END_TXT_RANK_OUTLINE_SZ = 1.0f;
		inline constexpr uint32_t END_TXT_CHAR_SZ = 80;
		inline constexpr uint32_t END_TXT_CONT_CHAR_SZ = 40;
		inline constexpr uint32_t END_TXT_RANK_CHAR_SZ = 48;
		inline constexpr std::string_view END_STR = "GAME OVER!";
		inline constexpr std::string_view END_CONT_STR = "Press SPACE to continue!";
		//Bg
		inline constexpr sf::Color END_BG_TINT = sf::Color({64, 0, 0, 255});

	//Assets
	inline constexpr std::string_view PATH_FONT = "assets/ClearSans-Regular.ttf";
	inline constexpr std::string_view PATH_TEX_BG = "assets/Background.png";
	inline constexpr std::string_view PATH_TEX_WALL = "assets/Wall32.png";
	inline constexpr std::string_view PATH_TEX_CEIL = "assets/Ceil32.png";
	inline constexpr std::string_view PATH_TEX_BUMP = "assets/Bumper.png";
	inline constexpr std::string_view PATH_TEX_BALL = "assets/Ball.png";
	inline constexpr std::string_view PATH_TEX_BLOCK = "assets/Block32.png";
}