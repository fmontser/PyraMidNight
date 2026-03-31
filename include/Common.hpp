#pragma once
#include <string>
#include <cstdint>
#include <SFML/Graphics.hpp>

namespace fknd {
	//Game
	inline constexpr uint32_t GAME_MAX_SCORE = std::numeric_limits<uint32_t>::max();
	inline constexpr uint8_t  GAME_MAX_CREDITS = std::numeric_limits<uint8_t>::max();
	inline constexpr uint8_t  GAME_RANK_SIZE = 10;
	inline constexpr uint8_t  GAME_FINAL_ROUND_ID = 1;

	//Ball
	inline constexpr float        BALL_INIT_SPEED = 0.6f;
	inline constexpr sf::Vector2f BALL_INIT_DIR = {-1, -1};
	inline constexpr sf::Vector2f BALL_INIT_POS = {256, 832};
	inline constexpr sf::Vector2f BALL_DOCKED_OFFSET = {64, -18};

	//Bumper
	inline constexpr float BMPR_INIT_SPEED = 0.45f;
	inline constexpr float BMPR_FINE_SPEED_MOD = 0.4f;
	inline constexpr float BMPR_COARSE_SPEED_MOD = 1.5f;
	inline constexpr float BMPR_MV_LIMIT_L = 32.0f;
	inline constexpr float BMPR_MV_LIMIT_R = 480.0f;
	inline constexpr float BMPR_ATK_DEADZONE = 0.6f;
	inline constexpr float BMPR_ATK_PWR = 2.22f;

	//Blocks
	
	//Score
	inline constexpr float   SCORE_BLOCK_MOD = 25.0f;
	inline constexpr int32_t SCORE_LOSE_BALL = -100;
	inline constexpr int32_t SCORE_TIME_PENALTY = -1;

	//Cursor
	inline constexpr float            CUR_MV_OFFSET = 30.0f;
	inline constexpr float            CUR_FONT_SZ = 48.0f;
	inline constexpr float            CUR_OUTLINE_SZ = 2.0f;
	inline constexpr sf::Color        CUR_OUTLINE_COL = sf::Color::Green;
	inline constexpr sf::Color        CUR_FILL_COL = sf::Color::Transparent;
	inline constexpr float            CUR_BLINK_TIME_SEC = 0.3f;
	inline constexpr std::string_view CUR_CHAR_SET = " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	//MenuScreenView
		inline constexpr float            MENU_TXT_OFFSET_Y = -96.0f;
		inline constexpr sf::Color        MENU_TXT_FILLCOL = sf::Color::White;
		inline constexpr sf::Color        MENU_TXT_OUTCOL = sf::Color::Blue;
		inline constexpr float            MENU_TXT_OUTLINE_SZ = 1.0f;
		inline constexpr uint32_t         MENU_TXT_CHAR_SZ = 48;
		inline constexpr std::string_view MENU_VOL_MUS_STR = "BGM VOLUME ";
		inline constexpr std::string_view MENU_VOL_SFX_STR = "SFX VOLUME ";
		inline constexpr std::string_view MENU_EXIT_STR = "EXIT GAME";
		inline constexpr float            MENU_VOL_STEP_SZ = 5.0f;
		inline constexpr int8_t           MENU_OPT_MAX = 3; 
		//Bg
		inline constexpr sf::Color        MENU_BG_TINT = sf::Color({255, 255, 255, 96});

	//TitleScreenView
		//Text
		inline constexpr float            TITLE_CREDITS_BLINK_TIME_SEC = 0.5f;
		inline constexpr sf::Color        TITLE_TXT_FILLCOL = sf::Color::Blue;
		inline constexpr sf::Color        TITLE_TXT_OUTCOL = sf::Color::Yellow;
		inline constexpr float            TITLE_TXT_OUTLINE_SZ = 3.0f;
		inline constexpr uint32_t         TITLE_TXT_CHAR_SZ = 90;
		inline constexpr uint32_t         TITLE_TXT_CREDITS_CHAR_SZ = 48;
		inline constexpr uint32_t         TITLE_TXT_START_CHAR_SZ = 40;
		inline constexpr std::string_view TITLE_STR = "FranKanoid";
		inline constexpr std::string_view TITLE_CREDITS_STR = "Insert coin! credits ";
		inline constexpr std::string_view TITLE_START_STR = "Press SPACE to start!";
		//Bg
		inline constexpr sf::Color        TITLE_BG_TINT = sf::Color({255, 255, 255, 255});


	//RoundScreenView
		//Text
		inline constexpr sf::Color        ROUND_TXT_FILLCOL = sf::Color::White;
		inline constexpr sf::Color        ROUND_TXT_OUTCOL = sf::Color::Blue;
		inline constexpr float            ROUND_TXT_OUTLINE_SZ = 1.0f;
		inline constexpr uint32_t         ROUND_TXT_CHAR_SZ = 24;
		inline constexpr std::string_view ROUND_CREDITS_STR = "CREDITS ";
		inline constexpr std::string_view ROUND_SCORE_STR = "SCORE ";
		//Bg
		inline constexpr sf::Color        ROUND_BG_TINT = sf::Color({0, 0, 255, 128});
		//Level
		inline constexpr u_int8_t         LVL_DIMENSIONS2 = 9;
		inline constexpr std::string_view LVL_CHAR_SET = "01";

	//EndScreenView
		//Text
		inline constexpr sf::Color        END_TXT_FILLCOL = sf::Color::Blue;
		inline constexpr sf::Color        END_TXT_OUTCOL = sf::Color::Yellow;
		inline constexpr float            END_TXT_OUTLINE_SZ = 4.0f;
		inline constexpr float            END_TXT_RANK_OUTLINE_SZ = 1.0f;
		inline constexpr uint32_t         END_TXT_CHAR_SZ = 80;
		inline constexpr uint32_t         END_TXT_CONT_CHAR_SZ = 40;
		inline constexpr uint32_t         END_TXT_RANK_CHAR_SZ = 48;
		inline constexpr std::string_view END_STR = "GAME OVER!";
		inline constexpr std::string_view END_CONT_STR = "Press SPACE to continue!";
		//Bg
		inline constexpr sf::Color END_BG_TINT = sf::Color({64, 0, 0, 255});

	//Assets
	inline constexpr std::string_view PATH_FONT = "assets/fonts/ClearSans-Regular.ttf";

	inline constexpr std::string_view PATH_TEX_BG = "assets/textures/Background.png";
	inline constexpr std::string_view PATH_TEX_WALL = "assets/textures/Wall32.png";
	inline constexpr std::string_view PATH_TEX_CEIL = "assets/textures/Ceil32.png";
	inline constexpr std::string_view PATH_TEX_BUMP = "assets/textures/Bumper.png";
	inline constexpr std::string_view PATH_TEX_BALL = "assets/textures/Ball.png";
	inline constexpr std::string_view PATH_TEX_BLOCK = "assets/textures/Block32.png";

	inline constexpr std::string_view PATH_AUD_BALL_BOUNCE = "assets/audio/BallBounce.ogg";
	inline constexpr std::string_view PATH_AUD_BALL_LOSE = "assets/audio/BallLose.ogg";
	inline constexpr std::string_view PATH_AUD_BALL_LAUNCH = "assets/audio/Launch.ogg";
	inline constexpr std::string_view PATH_AUD_BLOCK_DAMAGE = "assets/audio/BlockDamage.ogg";
	inline constexpr std::string_view PATH_AUD_BLOCK_DESTROY = "assets/audio/BlockDestroy.ogg";
	inline constexpr std::string_view PATH_AUD_BUMPER_BOUNCE = "assets/audio/BumperBounce.ogg";
	inline constexpr std::string_view PATH_AUD_PWRUP_0 = "assets/audio/PowerUp0.ogg";
	inline constexpr std::string_view PATH_AUD_ENEMY_SPAWN = "assets/audio/EnemySpawn.ogg";
	inline constexpr std::string_view PATH_AUD_COIN_IN = "assets/audio/Coin.ogg";
	inline constexpr std::string_view PATH_AUD_CURSOR = "assets/audio/Cursor.ogg";
	inline constexpr std::string_view PATH_AUD_NEXTROUND = "assets/audio/NextRound.ogg";
	inline constexpr std::string_view PATH_AUD_GAMEOVER = "assets/audio/GameOver.ogg";

	inline constexpr std::string_view PATH_AUD_MUSIC_0 = "assets/audio/MusicTheme0.ogg";

	//AudioManager
	inline constexpr float VOL_AUD_MAX = 100.0f;
	inline constexpr float VOL_AUD_MIN = 0.0f;
	inline constexpr float VOL_AUD_BGM = 60.0f;
	inline constexpr float VOL_AUD_SFX = 60.0f;
	inline constexpr float VOL_AUD_BALL_BOUNCE = 0.6f;
	inline constexpr float VOL_AUD_BALL_LOSE = 1.0f;
	inline constexpr float VOL_AUD_BALL_LAUNCH = 1.0f;
	inline constexpr float VOL_AUD_BLOCK_DESTROY = 0.9f;
	inline constexpr float VOL_AUD_BLOCK_DAMAGE = 1.0f; //TODO
	inline constexpr float VOL_AUD_ENEMY_SPAWN = 1.0f; //TODO enemies feature
	inline constexpr float VOL_AUD_BUMPER_BOUNCE = 0.4f;
	inline constexpr float VOL_AUD_PWRUP_0 = 1.0f;
	inline constexpr float VOL_AUD_COIN_IN = 1.0f;
	inline constexpr float VOL_AUD_CURSOR = 1.0f;
	inline constexpr float VOL_AUD_NEXTROUND = 1.0f;
	inline constexpr float VOL_AUD_GAMEOVER = 1.0f;
	inline constexpr float VOL_AUD_MUSIC_0 = 0.2f;

	//RenderManager (DO NOT EDIT RESOLUTION!!!)
	inline constexpr std::string_view RNDR_WINDOW_NAME = "FranKanoid";
	inline constexpr sf::Vector2u     RNDR_RESOLUTION = {640, 896};
	inline constexpr uint32_t         RNDR_FRAME_LIMIT = 60;

}