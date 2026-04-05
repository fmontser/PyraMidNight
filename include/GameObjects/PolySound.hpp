#pragma once
#include <SFML/Audio.hpp>
#include <string>


namespace pyramidnight {
	class PolySound : public sf::Sound {
		public:
			enum class Type {
				SFX, BGM
			};
	
			PolySound(const std::string_view& path, float gain, Type type);
			void SetInstanceVolume(float instanceGain);

		private:
			Type  mType;
			float mGain;

			float GetTypeVolume() const;

	};
}
