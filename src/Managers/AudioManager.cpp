#include <string>
#include <algorithm>
#include "AudioManager.hpp"
#include "ResourceManager.hpp"

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
		static sf::Clock cleanTimer;

		if (cleanTimer.getElapsedTime().asSeconds() > CLK_AUD_CLEAN_TIMER_S) {
			instance().Clean();
			cleanTimer.restart();
		}
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
		mSfx.erase(std::remove_if(mSfx.begin(), mSfx.end(),
			[](const std::unique_ptr<PolySound>& sound) {
				return !sound || (sound->getStatus() == PolySound::Status::Stopped);
			}),
			mSfx.end()
		);

		mBgm.erase(std::remove_if(mBgm.begin(), mBgm.end(),
			[](const std::unique_ptr<PolySound>& sound) {
				return !sound || (sound->getStatus() == PolySound::Status::Stopped);
			}),
			mBgm.end()
		);
	}

	void AudioManager::Init() { instance();	}
}
