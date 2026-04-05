#include <cmath>
#include "ResourceManager.hpp"
#include "AudioManager.hpp"
#include "PolySound.hpp"

namespace pyramidnight {

	PolySound::PolySound(Args args)
		: sf::Sound(*ResourceManager::GetAudio(args.path))
	{
		IsFadingOut = false;
		mType = args.type;
		mGain = args.gain;
		setVolume(GetTypeVolume() * mGain);
		setLooping(args.loop);
	}

	void PolySound::FadeOut(float gain) {
		static sf::Clock clk;
		setVolume(getVolume() * std::pow(gain, clk.restart().asSeconds()));
		if (getVolume() <= 0.1f)
			stop();
	}

	void PolySound::SetInstanceVolume(float instanceGain = 1.0f) {
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
