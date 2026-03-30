#include <cassert>
#include <string>
#include "ResourceManager.hpp"
#include "Levels.hpp"

namespace fknd {
	ResourceManager::ResourceManager() {
		ValidateLevels();
	}

	void ResourceManager::ValidateLevels() {
		assert(!ROUNDS.empty()
			&& "Error: No levels present");
		assert(GAME_FINAL_ROUND_ID == (ROUNDS.size() - 1)
			&& "Error: Wrong number of levels");

		for (const auto& level : ROUNDS) {
			assert(level.size() == LVL_DIMENSIONS2
				&& "Error: Wrong number of rows for a level");
			for (const auto& str : level) {
				assert(str.size() == LVL_DIMENSIONS2
					&& "Error: Wrong number of columns for a level");
				assert(str.find_first_not_of(LVL_CHAR_SET) == std::string::npos
					&& "Error: Invalid character on a level");
			}
		}
	}

}