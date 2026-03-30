#pragma once
#include <string>
#include <array>
#include "Common.hpp"

namespace fknd {

	const std::array<const std::string, LVL_DIMENSIONS2> LEVEL0 = {
		"000000000",
		"000000000",
		"000000000",
		"011111110",
		"000000000",
		"000000000",
		"000000000",
		"000000000",
		"000000000"
	};

	const std::array<const std::string, LVL_DIMENSIONS2> LEVEL1 = {
		"000000000",
		"000000000",
		"000000000",
		"011111110",
		"011111110",
		"000000000",
		"000000000",
		"000000000",
		"000000000"
	};

	const std::vector<std::array<const std::string, LVL_DIMENSIONS2>> ROUNDS {
		LEVEL0,
		LEVEL1
	};

}

