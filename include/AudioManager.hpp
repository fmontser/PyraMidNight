#pragma once
#include <SFML/Audio.hpp>
#include <memory>
#include "Common.hpp"

namespace fknd {
	
	class AudioManager {
		public:
			static void Init();

			static void Play(const std::string_view path, float volume, bool loop);

		private:
			AudioManager();
			AudioManager(const AudioManager&) = delete;
			AudioManager& operator=(const AudioManager&) = delete;

			std::vector<std::shared_ptr<sf::Sound>> mSounds;

			static AudioManager& instance() {
				static AudioManager inst;
				return inst;
			}
	};

}