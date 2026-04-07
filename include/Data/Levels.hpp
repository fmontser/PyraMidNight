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
		"001121100",
		"001121100",
		"000000000",
		"000000000",
		"000000000",
		"000000000"
	};

	const std::array<const std::string, LVL_DIMENSIONS2> LEVEL1 = {
		"000000000",
		"001010100",
		"000101000",
		"001010100",
		"000101000",
		"000000000",
		"000000000",
		"000000000",
		"000000000"
	};

		const std::array<const std::string, LVL_DIMENSIONS2> LEVEL2 = {
		"000000000",
		"000020000",
		"002212200",
		"000111000",
		"001111100",
		"003333300",
		"000000000",
		"000000000",
		"000000000"
	};

	const std::array<const std::string, LVL_DIMENSIONS2> LEVEL3 = {
	
		"020020020",
		"011131110",
		"000131000",
		"001131100",
		"000111000",
		"000000000",
		"000000000",
		"000000000",
		"000000000"
	};

	// add LEVEL here if declared above
	const std::vector<std::array<const std::string, LVL_DIMENSIONS2>> ROUNDS {
		LEVEL0,
		LEVEL1,
		LEVEL2,
		LEVEL3
	};

}

