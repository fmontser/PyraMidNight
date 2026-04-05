#pragma once
#include <SFML/Audio.hpp>
#include <string>

namespace pyramidnight {
	class PolySound : public sf::Sound {
		public:
			bool IsFadingOut;

			enum class Type {
				SFX, BGM
			};

			struct Args {
				const std::string_view& path;
				float                   gain;
				Type                    type;
				bool                    loop;
			};
			
			PolySound(Args args);
			
			void FadeOut(float gain);
			void SetInstanceVolume(float instanceGain);
			Type GetType() const;

		private:
			Type  mType;
			float mGain;

			float GetTypeVolume() const;

	};
}
