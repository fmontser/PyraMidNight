#pragma once
#include <SFML/Audio.hpp>
#include <memory>
#include "PolySound.hpp"
#include "Common.hpp"

namespace pyramidnight {
	
	class AudioManager {
		public:
			static void Init();

			static void Play(PolySound::Args args);
			static void SetBgmVolume(float volume);
			static void SetSfxVolume(float volume);
			static void Update();
			static uint8_t GetBgmVolume();
			static uint8_t GetSfxVolume();
			
		private:
			AudioManager();
			AudioManager(const AudioManager&) = delete;
			AudioManager& operator=(const AudioManager&) = delete;
			
			float                                   mBgmVolume;
			float                                   mSfxVolume;
			std::vector<std::unique_ptr<PolySound>> mBgm;
			std::vector<std::unique_ptr<PolySound>> mSfx;
			
			void Clean();

			static AudioManager& instance() {
				static AudioManager inst;
				return inst;
			}
		};
		
}