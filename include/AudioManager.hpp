#pragma once
#include <SFML/Audio.hpp>
#include <memory>
#include "Common.hpp"

namespace fknd {
	
	class AudioManager {
		public:
			static void Init();

			static void Play(const std::string_view path, float volume, bool loop);
			static void SetBgmVolume(uint32_t volume);
			static void SetSfxVolume(uint32_t volume);

		private:
			AudioManager();
			AudioManager(const AudioManager&) = delete;
			AudioManager& operator=(const AudioManager&) = delete;

			std::vector<std::shared_ptr<sf::Sound>> mBgm;
			std::vector<std::shared_ptr<sf::Sound>> mSfx;

			static AudioManager& instance() {
				static AudioManager inst;
				return inst;
			}
	};

}