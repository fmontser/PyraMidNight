#pragma once
#include <string>
#include <array>
#include "Common.hpp"

namespace fknd {

	const std::array<const std::string, LVL_DIMENSIONS2> LEVEL0 = {
		"000000000",
		"000000000",
		"000000000",
		"011121110",
		"011121110",
		"000000000",
		"000000000",
		"000000000",
		"000000000",
	};

	const std::array<const std::string, LVL_DIMENSIONS2> LEVEL1 = {
		"000000000",
		"001212100",
		"002121200",
		"001212100",
		"002121200",
		"000000000",
		"000000000",
		"000000000",
		"000000000"
	};

		const std::array<const std::string, LVL_DIMENSIONS2> LEVEL2 = {
		"000000000",
		"000020000",
		"000010000",
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
		"000000000",
	};

	const std::vector<std::array<const std::string, LVL_DIMENSIONS2>> ROUNDS {
		LEVEL0,
		LEVEL1,
		LEVEL2,
		LEVEL3
	};

}

