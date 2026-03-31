#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Common.hpp"

namespace fknd {
	
	class ResourceManager {
		public:
			struct ScoreEntry {
				std::string name;
				uint32_t    score;
			};

			struct SaveData {
				float bgmVol;
				float sfxVol;
				std::vector<ResourceManager::ScoreEntry> ranking;
			};


			static void Init();
			static std::shared_ptr<sf::Texture> GetTexture(const std::string_view path);
			static std::shared_ptr<sf::Font> GetFont(const std::string_view path);
			static std::shared_ptr<sf::SoundBuffer> GetAudio(const std::string_view path);
			static void SaveUserData(SaveData& data);
			static SaveData LoadUserData();
			
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

			std::vector<Texture> mTextures;
			std::vector<Font>    mFonts;
			std::vector<Audio>   mAudios;

			void InitSaveData();
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