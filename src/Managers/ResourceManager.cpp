#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
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

	void ResourceManager::Init() { 
		instance().InitSaveData();
	}

	std::shared_ptr<sf::Texture> ResourceManager::GetTexture(const std::string_view& path) {
		auto& vect = instance().mTextures;
		auto it = std::find_if(vect.begin(), vect.end(), [path](const Texture& tex) {
			return tex.path == path;
		});
		if (it != vect.end())
			return it->texture;
		else {
			std::cerr << "Error: Missing texture, failsafe loaded\n";
			return instance().mFailSafeTexture;
		}
	}

	std::shared_ptr<sf::Font> ResourceManager::GetFont(const std::string_view& path) {
		auto& vect = instance().mFonts;
		auto it = std::find_if(vect.begin(), vect.end(), [path](const Font& font) {
			return font.path == path;
		});
		if (it != vect.end())
			return it->font;
		else {
			std::cerr << "Error: Missing font, failsafe loaded\n";
			return instance().mFailSafeFont;
		}
	}

	std::shared_ptr<sf::SoundBuffer> ResourceManager::GetAudio(const std::string_view& path) {
		auto& vect = instance().mAudios;
		auto it = std::find_if(vect.begin(), vect.end(), [path](const Audio& audio) {
			return audio.path == path;
		});
		if (it != vect.end())
			return it->audio;
		else {
			std::cerr << "Error: Missing sound, failsafe loaded\n";
			return instance().mFailSafeSound;
		}
	}

	
	void ResourceManager::SaveUserData(SaveData& data)
	{
		try {
			uint32_t count = static_cast<uint32_t>(data.ranking.size());
			std::ofstream os("save.dat", std::ios::binary);

			os.write((char*)&data.bgmVol, sizeof(data.bgmVol));
			os.write((char*)&data.sfxVol, sizeof(data.sfxVol));
			os.write((char*)&count, sizeof(count));

			for (const auto& e : data.ranking) {
				uint32_t len = static_cast<uint32_t>(e.name.size());

				os.write((char*)&len, sizeof(len));
				os.write(e.name.data(), len);
				os.write((char*)&e.score, sizeof(e.score));
			}
		} catch (const std::exception& e){
			std::cerr << "Error: Filesystem error for save data file: " << e.what() << '\n';
		}
	}

	ResourceManager::SaveData ResourceManager::LoadUserData() {
		SaveData data;
		try {
			uint32_t count;
			std::ifstream is("save.dat", std::ios::binary);

			is.read((char*)&data.bgmVol, sizeof(data.bgmVol));
			is.read((char*)&data.sfxVol, sizeof(data.sfxVol));
			is.read((char*)&count, sizeof(count));
			data.ranking.resize(count);

			for (auto& e : data.ranking) {
				uint32_t len;

				is.read((char*)&len, sizeof(len));
				e.name.resize(len);
				is.read(&e.name[0], len);
				is.read((char*)&e.score, sizeof(e.score));
			}
		}
		catch(const std::exception& e) {
			std::cerr << "Error: Filesystem error for save data file: " << e.what() << '\n';
		}
		return data;
	}

	void ResourceManager::InitSaveData() {
		SaveData data;
		std::vector<ScoreEntry> ranking;
		
		if (std::filesystem::exists(PATH_SAVE_DATA))
			return;
			
		ranking.push_back({"RAA", 100000});
		ranking.push_back({"ELI", 90000});
		ranking.push_back({"JMA", 80000});
		ranking.push_back({"IOQ", 70000});
		ranking.push_back({"FFF", 60000});
		ranking.push_back({"ISS", 3000});
		ranking.push_back({"YSS", 1000});
		ranking.push_back({"PAS", 500});
		ranking.push_back({"TOI", 200});
		ranking.push_back({"CAN", 10});
		
		data.bgmVol = VOL_AUD_BGM;
		data.sfxVol = VOL_AUD_SFX;
		data.ranking = ranking;
		SaveUserData(data);
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
		std::vector<std::string_view> filePaths {
			PATH_TEX_BG,
			PATH_TEX_WALL, 
			PATH_TEX_CEIL, 
			PATH_TEX_BUMP, 
			PATH_TEX_BALL, 
			PATH_TEX_BLOCK
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
		std::vector<std::string_view> filePaths {
			PATH_FONT
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
			exit(1);
		}
	}
	void ResourceManager::LoadAudio() {
		std::vector<std::string_view> filePaths {
			PATH_AUD_BALL_BOUNCE,
			PATH_AUD_BALL_LOSE,
			PATH_AUD_BALL_LAUNCH,
			PATH_AUD_BLOCK_DAMAGE,
			PATH_AUD_BLOCK_DESTROY,
			PATH_AUD_BUMPER_BOUNCE,
			PATH_AUD_PWRUP_0,
			PATH_AUD_ENEMY_SPAWN,
			PATH_AUD_COIN_IN,
			PATH_AUD_CURSOR,
			PATH_AUD_NEXTROUND,
			PATH_AUD_GAMEOVER,
			PATH_AUD_MUSIC_0
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
			exit(1);
		}
	}

}