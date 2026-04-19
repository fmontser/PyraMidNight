#pragma once
#include <string>
#include <array>
#include "Common.hpp"

namespace pyramidnight {

	// 9x9 max, valid characters on LVL_CHAR_SET (Common.hpp), the add to ROUNDS, see below
	const std::array<const std::string, LVL_DIMENSIONS2> LEVEL0 = {
		"000000000",
		"000000000",
		"000000000",
		"111111111",
		"111111111",
		"111111111",
		"000000000",
		"000000000",
		"000000000"
	};

	const std::array<const std::string, LVL_DIMENSIONS2> LEVEL1 = {
		"000000000",
		"000000000",
		"002222200",
		"001111100",
		"001111100",
		"001111100",
		"000000000",
		"000000000",
		"000000000"
	};

		const std::array<const std::string, LVL_DIMENSIONS2> LEVEL2 = {
		"000000000",
		"000000000",
		"001111100",
		"002222200",
		"003333300",
		"000000000",
		"000000000",
		"000000000",
		"000000000"
	};

	const std::array<const std::string, LVL_DIMENSIONS2> LEVEL3 = {
	
		"000000000",
		"002111200",
		"002111200",
		"002111200",
		"002111200",
		"002111200",
		"002111200",
		"002111200",
		"000000000"
	};

	// add LEVEL here if declared above, then change GAME_FINAL_ROUND_ID on Commmon.hpp
	const std::vector<std::array<const std::string, LVL_DIMENSIONS2>> ROUNDS {
		LEVEL0,
		LEVEL1,
		LEVEL2,
		LEVEL3
	};

}

