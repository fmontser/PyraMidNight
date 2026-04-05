#include "ResourceManager.hpp"
#include "AudioManager.hpp"
#include "PolySound.hpp"

namespace pyramidnight {
	PolySound::PolySound(const std::string_view& path, float gain, Type type)
		: sf::Sound(*ResourceManager::GetAudio(path))
	{
		mType = type;
		mGain = gain;
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
