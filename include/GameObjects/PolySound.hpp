#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <memory>

namespace pyramidnight {
	
	// enables polyphonic sound and effects
	class PolySound : public sf::Sound {
		public:
			bool IsFadingOut;

			enum class Type {
				SFX, BGM
			};

			struct Args {
				std::shared_ptr<sf::SoundBuffer> buffer;
				float gain;
				Type  type;
				bool  loop;
			};
			
			PolySound(Args args, float& trackVolume);
			
			void FadeOut(float gain, const sf::Time& deltaTime);
			void SetInstanceVolume(float instanceGain);
			Type GetType() const;

		private:
			Args   mArgs;
			Type   mType;
			float  mGain;
			float& mTrackVolume;



	};
}
