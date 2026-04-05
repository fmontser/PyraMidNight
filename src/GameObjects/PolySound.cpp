#include "ResourceManager.hpp"
#include "AudioManager.hpp"
#include "PolySound.hpp"

namespace pyramidnight {

	PolySound::PolySound(Args args)
		: sf::Sound(*ResourceManager::GetAudio(args.path))
	{
		mType = args.type;
		mGain = args.gain;
		setVolume(GetTypeVolume() * mGain);
	}

	void PolySound::SetInstanceVolume(float instanceGain) {
		setVolume(GetTypeVolume() * mGain * instanceGain);
	}

	float PolySound::GetTypeVolume() const
	{
		float typeVolume = 100.0f;
		switch (mType) {
			case Type::SFX: typeVolume = AudioManager::GetSfxVolume(); break;
			case Type::BGM: typeVolume = AudioManager::GetBgmVolume(); break;
			default: break;
		}
		return typeVolume;
	}
}
