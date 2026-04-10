#pragma once
#include <map>
#include <vector>
#include <optional>
#include "PowerUp.hpp"
#include "ICollidable.hpp"

namespace pyramidnight {

	class Spawner {
		public:
			Spawner();

			std::optional<PowerUp::Type> RollSpawn();

		private:
			std::map<float, PowerUp::Type> mBlockChanceMap;

			float GenerateRoll();
	};

}