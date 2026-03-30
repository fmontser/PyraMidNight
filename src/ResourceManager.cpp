#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iostream>

#include "ResourceManager.hpp"
#include "Levels.hpp"

namespace fknd {
	
	ResourceManager::ResourceManager() {
		ValidateLevels();
		LoadTextures();
		LoadFonts();
		LoadAudio();
	}

	void ResourceManager::Init() { instance(); }

	std::shared_ptr<sf::Texture> ResourceManager::GetTexture(const std::string_view path) {
		auto& vect = instance().mTextures;
		auto it = std::find_if(vect.begin(), vect.end(), [path](const Texture& tex) {
			return tex.path == path;
		});
		if (it != vect.end())
			return it->texture;
	}

	std::shared_ptr<sf::Font> ResourceManager::GetFont(const std::string_view path) {
		auto& vect = instance().mFonts;
		auto it = std::find_if(vect.begin(), vect.end(), [path](const Font& font) {
			return font.path == path;
		});
		if (it != vect.end())
			return it->font;
	}

	std::shared_ptr<sf::SoundBuffer> ResourceManager::GetAudio(const std::string_view path) {
		auto& vect = instance().mAudios;
		auto it = std::find_if(vect.begin(), vect.end(), [path](const Audio& audio) {
			return audio.path == path;
		});
		if (it != vect.end())
			return it->audio;
	}

	void ResourceManager::ValidateLevels() {
		assert(!ROUNDS.empty()
			&& "Error: No levels present");
		assert(GAME_FINAL_ROUND_ID == (ROUNDS.size() - 1)
			&& "Error: Wrong number of levels");

		for (const auto& level : ROUNDS) {
			assert(level.size() == LVL_DIMENSIONS2
				&& "Error: Wrong number of rows for a level");
			for (const auto& str : level) {
				assert(str.size() == LVL_DIMENSIONS2
					&& "Error: Wrong number of columns for a level");
				assert(str.find_first_not_of(LVL_CHAR_SET) == std::string::npos
					&& "Error: Invalid character on a level");
			}
		}
	}

	void ResourceManager::LoadTextures() {
		std::vector<std::string_view> filePaths {
			PATH_TEX_BG,
			PATH_TEX_WALL, 
			PATH_TEX_CEIL, 
			PATH_TEX_BUMP, 
			PATH_TEX_BALL, 
			PATH_TEX_BLOCK
		};

		try {
				for (const auto& path : filePaths) {
					auto texture = Texture {
						path,
						std::make_shared<sf::Texture>(path)
					};
				mTextures.push_back(texture);
				}
		} catch(const sf::Exception& e) {
			std::cerr << "Error: Missing or wrong texture file: " << e.what() << '\n';
			exit(1);
		}
	}
	void ResourceManager::LoadFonts()
	{
		std::vector<std::string_view> filePaths {
			PATH_FONT
		};

		try {
				for (const auto& path : filePaths) {
					auto font = Font {
						path,
						std::make_shared<sf::Font>(path)
					};
				mFonts.push_back(font);
				}
		} catch(const sf::Exception& e) {
			std::cerr << "Error: Missing or wrong font file: " << e.what() << '\n';
			exit(1);
		}
	}
	void ResourceManager::LoadAudio() {
		std::vector<std::string_view> filePaths {
			PATH_AUD_BALL_BOUNCE,
			PATH_AUD_BALL_LOSE,
			PATH_AUD_BLOCK_DAMAGE,
			PATH_AUD_BLOCK_DESTROY,
			PATH_AUD_BUMPER_BOUNCE,
			PATH_AUD_ENEMY_SPAWN,
			PATH_AUD_COIN_IN,
			PATH_AUD_CURSOR,
			PATH_AUD_NEXTROUND,
			PATH_AUD_GAMEOVER,
			PATH_AUD_MUSIC_0
		};

		try {
				for (const auto& path : filePaths) {
					auto audio = Audio {
						path,
						std::make_shared<sf::SoundBuffer>(path)
					};
				mAudios.push_back(audio);
				}
		} catch(const sf::Exception& e) {
			std::cerr << "Error: Missing or wrong audio file: " << e.what() << '\n';
			exit(1);
		}
	}
}