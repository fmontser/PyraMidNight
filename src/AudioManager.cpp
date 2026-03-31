#include <string>
#include "AudioManager.hpp"
#include "ResourceManager.hpp"

namespace fknd {

	AudioManager::AudioManager() {}

	void AudioManager::SetBgmVolume(uint32_t volume) {
		auto& bgm = instance().mBgm;
		for (auto& sound : bgm){
			sound->setVolume(volume);
		}
	}

	void AudioManager::SetSfxVolume(uint32_t volume) {
		auto& sfx = instance().mSfx;
		for (auto& sound : sfx){
			sound->setVolume(volume);
		}
	}

	void AudioManager::Init() { instance(); }

	void fknd::AudioManager::Play(const std::string_view path, float volume, bool loop) {
		auto sound = std::make_shared<sf::Sound>(*ResourceManager::GetAudio(path));
		if (path.find("Music",0) != std::string::npos)
			instance().mBgm.push_back(sound);
		else
			instance().mSfx.push_back(sound);
		sound->setLooping(loop);
		sound->setVolume(sound->getVolume() * volume);
		sound->play();
	}
}
