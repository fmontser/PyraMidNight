#include <string>
#include <algorithm>
#include "AudioManager.hpp"
#include "ResourceManager.hpp"

namespace fknd {

	AudioManager::AudioManager() {}

	void AudioManager::SetBgmVolume(float volume) {
		auto& bgm = instance().mBgm;
		instance().mBgmVolume = volume;
		auto test = instance().mBgmVolume;
		for (auto& sound : bgm){
			sound->setVolume(volume);
		}
	}

	void AudioManager::SetSfxVolume(float volume) {
		auto& sfx = instance().mSfx;
		instance().mSfxVolume = volume;
		for (auto& sound : sfx){
			sound->setVolume(volume);
		}
	}

	uint8_t AudioManager::GetBgmVolume() { return instance().mBgmVolume; }

	uint8_t AudioManager::GetSfxVolume() { return instance().mSfxVolume; }

	void AudioManager::Init() { instance();	}

	void fknd::AudioManager::Play(const std::string_view path, float volume, bool loop) {
		auto sound = std::make_shared<sf::Sound>(*ResourceManager::GetAudio(path));
		if (path.find("Music",0) != std::string::npos) {
			instance().mBgm.push_back(sound);
			sound->setVolume(std::clamp(instance().mBgmVolume * volume, VOL_AUD_MIN, VOL_AUD_MAX));
			SetBgmVolume(instance().mBgmVolume);
		}
		else {
			instance().mSfx.push_back(sound);
			sound->setVolume(std::clamp(instance().mSfxVolume * volume, VOL_AUD_MIN, VOL_AUD_MAX));
			SetSfxVolume(instance().mSfxVolume);
		}
		sound->setLooping(loop);
		sound->play();
	}
}
