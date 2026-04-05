#pragma once
#include <SFML/Audio.hpp>
#include <string>


namespace pyramidnight {
	class PolySound : public sf::Sound {
		public:
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
			void SetInstanceVolume(float instanceGain);

		private:
			Type  mType;
			float mGain;

			float GetTypeVolume() const;

	};
}
