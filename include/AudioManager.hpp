#pragma once
#include <SFML/Audio.hpp>
#include "Common.hpp"

namespace fknd {
	
	class AudioManager {
		public:
			static void Init();

		private:

			AudioManager();
			AudioManager(const AudioManager&) = delete;
			AudioManager& operator=(const AudioManager&) = delete;

			static AudioManager& instance() {
				static AudioManager inst;
				return inst;
			}
	};

}