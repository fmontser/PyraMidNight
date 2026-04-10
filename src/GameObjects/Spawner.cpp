#include <algorithm>
#include <random>
#include "Spawner.hpp"

namespace pyramidnight {
	
	//TODO replace hardcoded values
	Spawner::Spawner() {
		mBlockChanceMap [0.16f] = PowerUp::Type::SCORE;
	}

	std::optional<PowerUp::Type> Spawner::RollSpawn() {

			float roll = 0.15f; //GenerateRoll();

			auto it = std::find_if(mBlockChanceMap.begin(), mBlockChanceMap.end(),
			[roll](const auto& entry) {
				return entry.first <= roll;
			});
			if (it != mBlockChanceMap.end())
				return it->second;
			else
				return std::nullopt;
	}

	float Spawner::GenerateRoll() {
		static std::random_device rd; 
		static std::mt19937 gen(rd()); 

		std::uniform_real_distribution<float> dis(0.0f, 1.0f);
		return dis(gen);
	}
}