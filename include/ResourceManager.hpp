#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Common.hpp"

namespace fknd {
	
	class ResourceManager {
		public:
			static void Init();
			static std::shared_ptr<sf::Texture> GetTexture(const std::string_view path);
			static std::shared_ptr<sf::Font> GetFont(const std::string_view path);
			
		private:
			struct Texture {
				std::string_view             path;
				std::shared_ptr<sf::Texture> texture;
			};

			struct Font {
				std::string_view          path;
				std::shared_ptr<sf::Font> font;
			};

			ResourceManager();
			ResourceManager(const ResourceManager&) = delete;
			ResourceManager& operator=(const ResourceManager&) = delete;

			std::vector<Texture> mTextures;
			std::vector<Font>    mFonts;

			void ValidateLevels();
			void LoadTextures();
			void LoadFonts();

			static ResourceManager& instance() {
				static ResourceManager inst;
				return inst;
			}
	};

}