#pragma once
#include <SFML/Audio.hpp>
#include <memory>
#include "Common.hpp"

namespace fknd {
	
	class AudioManager {
		public:
			static void Init();

			static void Play(const std::string_view path, float volume, bool loop);
			static void SetBgmVolume(float volume);
			static void SetSfxVolume(float volume);
			static float GetBgmVolume();
			static float GetSfxVolume();

		private:
			AudioManager();
			AudioManager(const AudioManager&) = delete;
			AudioManager& operator=(const AudioManager&) = delete;

			float mBgmVolume;
			float mSfxVolume;
			std::vector<std::shared_ptr<sf::Sound>> mBgm;
			std::vector<std::shared_ptr<sf::Sound>> mSfx;

			static AudioManager& instance() {
				static AudioManager inst;
				return inst;
			}
	};

}