#include <algorithm>
#include <cassert>
#include <iostream>
#include "ResourceManager.hpp"
#include "Levels.hpp"
#include "FailSafeData.hpp"

namespace pyramidnight {
	
	ResourceManager::ResourceManager() {
		ValidateLevels();
		LoadTextures();
		LoadFonts();
		LoadAudio();
	}

	void ResourceManager::Init() { instance(); }

	const std::shared_ptr<sf::Texture>& ResourceManager::GetTexture(const std::string_view& path) {
		auto& vect = instance().mTextures;
		auto it = std::find_if(vect.begin(), vect.end(), [path](const Texture& tex) {
			return tex.path == path;
		});
		if (it != vect.end())
			return it->texture;
		else {
			// failsafe, returns checkered sprite
			std::cerr << "Error: Missing texture, failsafe loaded\n";
			return instance().mFailSafeTexture;
		}
	}

	const std::shared_ptr<sf::Font>& ResourceManager::GetFont(const std::string_view& path) {
		auto& vect = instance().mFonts;
		auto it = std::find_if(vect.begin(), vect.end(), [path](const Font& font) {
			return font.path == path;
		});
		if (it != vect.end())
			return it->font;
		else {
			// failsafe, returns the default font (its the same at the moment)
			std::cerr << "Error: Missing font, failsafe loaded\n";
			return instance().mFailSafeFont;
		}
	}

	const std::shared_ptr<sf::SoundBuffer>& ResourceManager::GetAudio(const std::string_view& path) {
		auto& vect = instance().mAudios;
		auto it = std::find_if(vect.begin(), vect.end(), [path](const Audio& audio) {
			return audio.path == path;
		});
		if (it != vect.end())
			return it->audio;
		else {
			// failsafe, returns an audible tone
			std::cerr << "Error: Missing sound, failsafe loaded\n";
			return instance().mFailSafeSound;
		}
	}

	void ResourceManager::ValidateLevels()
	{
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
		std::vector<std::string> filePaths {
			std::string(PATH_TEX_BG),
			std::string(PATH_TEX_WALL), 
			std::string(PATH_TEX_CEIL), 
			std::string(PATH_TEX_BUMP), 
			std::string(PATH_TEX_BALL), 
			std::string(PATH_TEX_BLOCK),
			std::string(PATH_TEX_SCORE_PWRUP)
		};

		mFailSafeTexture = std::make_shared<sf::Texture>(FAILSAFE_TEXTURE_DATA, FAILSAFE_TEXTURE_DATA_SZ);
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
		}
	}
	void ResourceManager::LoadFonts()
	{
		std::vector<std::string> filePaths {
			std::string(PATH_FONT)
		};

		mFailSafeFont = std::make_shared<sf::Font>(FAILSAFE_FONT_DATA, FAILSAFE_FONT_DATA_SZ);
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
		}
	}
	void ResourceManager::LoadAudio() {
		std::vector<std::string> filePaths {
			std::string(PATH_AUD_BALL_BOUNCE),
			std::string(PATH_AUD_BALL_LOSE),
			std::string(PATH_AUD_BALL_LAUNCH),
			std::string(PATH_AUD_BLOCK_DAMAGE),
			std::string(PATH_AUD_BLOCK_DESTROY),
			std::string(PATH_AUD_BUMPER_BOUNCE),
			std::string(PATH_AUD_PWRUP_0),
			std::string(PATH_AUD_ENEMY_SPAWN),
			std::string(PATH_AUD_COIN_IN),
			std::string(PATH_AUD_CURSOR),
			std::string(PATH_AUD_NEXTROUND),
			std::string(PATH_AUD_GAMEOVER),
			std::string(PATH_AUD_MUSIC_0)
		};

		mFailSafeSound = std::make_shared<sf::SoundBuffer>(FAILSAFE_SOUND_DATA, FAILSAFE_SOUND_DATA_SZ);
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
		}
	}

}