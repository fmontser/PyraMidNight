#include <cmath>
#include "PolySound.hpp"

namespace pyramidnight {

	PolySound::PolySound(Args args, float& trackVolume) :
		sf::Sound(*args.buffer),
		mArgs(args),
		mTrackVolume(trackVolume)
	{
		IsFadingOut = false;
		mType = mArgs.type;
		mGain = mArgs.gain;
		setVolume(mTrackVolume * mGain);
		setLooping(mArgs.loop);
	}

	void PolySound::FadeOut(float gain, const sf::Time& deltaTime) {
		auto soundBufferVolume = getVolume();
		setVolume(soundBufferVolume * std::pow(gain, deltaTime.asSeconds()));
		if (soundBufferVolume <= 0.1f)
			stop();
	}

	void PolySound::SetInstanceVolume(float instanceGain = 1.0f) {
		setVolume(mTrackVolume * mGain * instanceGain);
	}

	PolySound::Type PolySound::GetType() const { return mType;	}
}
