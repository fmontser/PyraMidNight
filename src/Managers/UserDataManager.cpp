#include <filesystem>
#include <fstream>
#include <iostream>
#include "UserDataManager.hpp"
#include "Common.hpp"

namespace pyramidnight {
		
	void UserDataManager::Init() {
		instance().InitSaveData();
	}

	void UserDataManager::SaveUserData() {
		std::string path(PATH_SAVE_DATA);
		auto& data = instance().mSaveData;

		try {
			uint32_t count = static_cast<uint32_t>(data.ranking.size());
			std::ofstream outStream(path, std::ios::binary);

			outStream.write((char*)&data.bgmVol, sizeof(data.bgmVol));
			outStream.write((char*)&data.sfxVol, sizeof(data.sfxVol));

			outStream.write((char*)&count, sizeof(count));
			for (const auto& record : data.ranking) {
				uint32_t len = static_cast<uint32_t>(record.name.size());

				outStream.write((char*)&len, sizeof(len));
				outStream.write(record.name.data(), len);
				outStream.write((char*)&record.score, sizeof(record.score));
			}
		} catch (const std::exception& e){
			std::cerr << "Error: Filesystem error for save data file: " << e.what() << '\n';
		}
	}

	void UserDataManager::LoadUserData() {
		std::string path(PATH_SAVE_DATA);
		auto& data = instance().mSaveData;

		try {
			uint32_t count {};
			std::ifstream inStream(path, std::ios::binary);

			inStream.read((char*)&data.bgmVol, sizeof(data.bgmVol));
			inStream.read((char*)&data.sfxVol, sizeof(data.sfxVol));
			inStream.read((char*)&count, sizeof(count));

			data.ranking.resize(count);
			for (auto& record : data.ranking) {
				uint32_t len {};

				inStream.read((char*)&len, sizeof(len));
				record.name.resize(len);
				inStream.read(&record.name[0], len);
				inStream.read((char*)&record.score, sizeof(record.score));
			}
		}
		catch(const std::exception& e) {
			std::cerr << "Error: Filesystem error for save data file: " << e.what() << '\n';
		}
	}

	void UserDataManager::SaveBgmVolume() {
		//TODO
	}

	void UserDataManager::SaveSfxVolume() {
		//TODO
	}

	void UserDataManager::SaveScoreRanking() {
		//TODO
	}

	void UserDataManager::InitSaveData() {
		auto& data = instance().mSaveData;
		std::vector<ScoreEntry> ranking {};
		
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
		SaveUserData();
	}

}

