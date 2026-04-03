#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "UserDataManager.hpp"
#include "Common.hpp"

namespace pyramidnight {

	UserDataManager::UserDataManager() {
		InitSaveData();
		LoadUserData();
	}

	void UserDataManager::Init() { instance(); }

	void UserDataManager::SaveBgmVolume(float volume) {
		instance().mSaveData.bgmVol =  volume;
		instance().SaveUserData();
	}

	void UserDataManager::SaveSfxVolume(float volume) {
		instance().mSaveData.sfxVol =  volume;
		instance().SaveUserData();
	}

	void UserDataManager::SaveRecord(const std::string& name, uint32_t score) {
		auto& data = instance().mSaveData;

		data.ranking.push_back({name, score});
		instance().SortRanking();
		if (data.ranking.size() > GAME_RANK_SIZE)
			data.ranking.pop_back();
		instance().SaveUserData();
	}

	UserDataManager::SaveData& UserDataManager::GetUserData() { return instance().mSaveData; }

	void UserDataManager::SaveUserData() {
		std::string path(PATH_SAVE_DATA);

		try {
			uint32_t count = static_cast<uint32_t>(mSaveData.ranking.size());
			std::ofstream outStream(path, std::ios::binary);

			outStream.write((char*)&mSaveData.bgmVol, sizeof(mSaveData.bgmVol));
			outStream.write((char*)&mSaveData.sfxVol, sizeof(mSaveData.sfxVol));

			outStream.write((char*)&count, sizeof(count));
			for (const auto& record : mSaveData.ranking) {
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

		try {
			uint32_t count {};
			std::ifstream inStream(path, std::ios::binary);

			inStream.read((char*)&mSaveData.bgmVol, sizeof(mSaveData.bgmVol));
			inStream.read((char*)&mSaveData.sfxVol, sizeof(mSaveData.sfxVol));
			inStream.read((char*)&count, sizeof(count));

			mSaveData.ranking.resize(count);
			for (auto& record : mSaveData.ranking) {
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

	void UserDataManager::InitSaveData() {
		std::vector<ScoreEntry> ranking {};
		
		if (std::filesystem::exists(PATH_SAVE_DATA))
			return;
		
		ranking.push_back({"RA ", 100000});
		ranking.push_back({"ELI", 90000});
		ranking.push_back({"JMA", 80000});
		ranking.push_back({"IOQ", 70000});
		ranking.push_back({"FFF", 60000});
		ranking.push_back({"ISS", 3000});
		ranking.push_back({"YSS", 1000});
		ranking.push_back({"PAS", 500});
		ranking.push_back({"TOI", 200});
		ranking.push_back({"CAN", 10});
		
		mSaveData.bgmVol = VOL_AUD_BGM;
		mSaveData.sfxVol = VOL_AUD_SFX;
		mSaveData.ranking = ranking;
		SaveUserData();
	}
	
	void UserDataManager::SortRanking() {
		std::sort(mSaveData.ranking.begin(), mSaveData.ranking.end(),
		[](const ScoreEntry& a, const ScoreEntry& b) {
			return a.score > b.score;
		});
	}
}

