#include <algorithm>
#include <random>
#include "Spawner.hpp"
#include "Common.hpp"

namespace pyramidnight {
	
	Spawner::Spawner() {
		mBlockChanceMap [PWRUP_SCORE_CHANCE] = PowerUp::Type::SCORE;
		mBlockChanceMap [1.0f] = PowerUp::Type::CREDIT;
	}

	std::optional<PowerUp::Type> Spawner::RollSpawn() {

			float roll = GenerateRoll();

			auto it = std::find_if(mBlockChanceMap.begin(), mBlockChanceMap.end(),
			[roll](const auto& entry) {
				return entry.first >= roll;
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