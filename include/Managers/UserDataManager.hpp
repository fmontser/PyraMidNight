#pragma once
#include <string>
#include <cstdint>
#include <vector>

namespace pyramidnight {

	class UserDataManager {
		public:
			struct ScoreEntry {
				std::string name;
				uint32_t    score;
			};

			struct SaveData {
				float bgmVol;
				float sfxVol;
				std::vector<ScoreEntry> ranking;
			};

			static void Init();
			static void SaveUserData();
			static void LoadUserData();
			static void SaveBgmVolume();
			static void SaveSfxVolume();
			static void SaveScoreRanking();

		private:
			UserDataManager();
			UserDataManager(const UserDataManager& src) = delete;
			UserDataManager& operator=(const UserDataManager& src) = delete;

			static UserDataManager& instance() {
				static UserDataManager inst;
				return inst;
			}

			SaveData mSaveData;

			void InitSaveData();
	};

}