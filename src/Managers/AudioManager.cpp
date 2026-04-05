#include <string>
#include <algorithm>
#include "AudioManager.hpp"
#include "ResourceManager.hpp"

namespace pyramidnight {

	AudioManager::AudioManager() {}

	void AudioManager::SetBgmVolume(float volume) {
		auto& bgm = instance().mBgm;
		instance().mBgmVolume = volume;
		for (auto& sound : bgm){
			sound->SetInstanceVolume(1.0f);
		}
	}

	void AudioManager::SetSfxVolume(float volume) {
		auto& sfx = instance().mSfx;
		instance().mSfxVolume = volume;
		for (auto& sound : sfx){
			sound->SetInstanceVolume(1.0f);
		}
	}

	uint8_t AudioManager::GetBgmVolume() { return instance().mBgmVolume; }

	uint8_t AudioManager::GetSfxVolume() { return instance().mSfxVolume; }

	void AudioManager::Init() { instance();	}

	void pyramidnight::AudioManager::Play(PolySound::Args args) {
		auto sound = std::make_unique<PolySound>(args);
		
		sound->play();
		switch (args.type) {
			case PolySound::Type::BGM: instance().mBgm.push_back(std::move(sound)); break;
			case PolySound::Type::SFX: instance().mSfx.push_back(std::move(sound)); break;
			default: break;
		}
	}
}
