#include "AudioManager.hpp"
#include "ResourceManager.hpp"

namespace fknd {

	AudioManager::AudioManager() {}

	void AudioManager::Init() { instance(); }

	void fknd::AudioManager::Play(const std::string_view path, float volume, bool loop) {
		auto sound = std::make_shared<sf::Sound>(*ResourceManager::GetAudio(path));
		instance().mSounds.push_back(sound);
		sound->setLooping(loop);
		sound->setVolume(sound->getVolume() * volume);
		sound->play();
	}
}
