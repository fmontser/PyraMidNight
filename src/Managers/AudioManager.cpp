#include <string>
#include <algorithm>
#include "AudioManager.hpp"
#include "ResourceManager.hpp"

//TODO delete
#include <iostream>

namespace pyramidnight {

	AudioManager::AudioManager() {}

	//TODO Master volume levels

	void AudioManager::Play(PolySound::Args args) {
		auto sound = std::make_unique<PolySound>(args);
		
		sound->play();
		switch (args.type) {
			case PolySound::Type::BGM: instance().mBgm.push_back(std::move(sound)); break;
			case PolySound::Type::SFX: instance().mSfx.push_back(std::move(sound)); break;
			default: break;
		}
	}

	void AudioManager::Update() {
		//TODO
	}

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

	void AudioManager::Clean() {
		auto& sfx = instance().mSfx;

		sfx.erase(std::remove_if(sfx.begin(), sfx.end(),
			[](const std::unique_ptr<PolySound>& sound) {
				return !sound || (sound->getStatus() == PolySound::Status::Stopped);
			}),
			sfx.end()
		);

		sfx.erase(std::remove_if(sfx.begin(), sfx.end(),
			[](const std::unique_ptr<PolySound>& sound) {
				return !sound || (sound->getStatus() == PolySound::Status::Stopped);
			}),
			sfx.end()
		);
	}

	void AudioManager::Init() { instance();	}
}
