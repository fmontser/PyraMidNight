#include <string>
#include <algorithm>
#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include "RenderManager.hpp"

namespace pyramidnight {

	AudioManager::AudioManager() {}

	void AudioManager::Play(PolySound::Args args) {
		auto sound = std::make_unique<PolySound>(args);
		
		sound->play();
		switch (args.type) {
			case PolySound::Type::BGM: instance().mBgm.push_back(std::move(sound)); break;
			case PolySound::Type::SFX: instance().mSfx.push_back(std::move(sound)); break;
			default: break;
		}
	}
	
	void AudioManager::FadeOutBgm() {
		for (auto& sound: instance().mBgm) {
			sound->IsFadingOut = true;
		}
	}

	void AudioManager::Update() {
		static float timeElapsed = 0.0f;

		// clean stopped
		timeElapsed += RenderManager::GetDeltaTime().asSeconds();
		if (timeElapsed > CLK_AUD_CLEAN_TIMER_S) {
			instance().Clean();
			timeElapsed = 0.0f;
		}

		// fade bgm
		for (auto& sound: instance().mBgm) {
			if (sound->IsFadingOut)
				sound->FadeOut(0.65f);
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
