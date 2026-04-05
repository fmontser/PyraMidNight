#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Common.hpp"

namespace pyramidnight {
	
	class ResourceManager {
		public:
			static void Init();
			static const std::shared_ptr<sf::Texture>&     GetTexture(const std::string_view& path);
			static const std::shared_ptr<sf::Font>&        GetFont(const std::string_view& path);
			static const std::shared_ptr<sf::SoundBuffer>& GetAudio(const std::string_view& path);

		private:
			struct Texture {
				std::string_view             path;
				std::shared_ptr<sf::Texture> texture;
			};

			struct Font {
				std::string_view          path;
				std::shared_ptr<sf::Font> font;
			};

			struct Audio {
				std::string_view                 path;
				std::shared_ptr<sf::SoundBuffer> audio;
			};

			ResourceManager();
			ResourceManager(const ResourceManager&) = delete;
			ResourceManager& operator=(const ResourceManager&) = delete;

			std::vector<Texture>             mTextures;
			std::shared_ptr<sf::Texture>     mFailSafeTexture;
			std::vector<Font>                mFonts;
			std::shared_ptr<sf::Font>        mFailSafeFont;
			std::vector<Audio>               mAudios;
			std::shared_ptr<sf::SoundBuffer> mFailSafeSound;

			void ValidateLevels();
			void LoadTextures();
			void LoadFonts();
			void LoadAudio();

			static ResourceManager& instance() {
				static ResourceManager inst;
				return inst;
			}
	};

}