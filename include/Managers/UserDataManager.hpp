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
				bool        actual;
			};

			struct SaveData {
				float bgmVol;
				float sfxVol;
				std::vector<ScoreEntry> ranking;
			};
			
			static void Init();
			static void SaveBgmVolume(float volume);
			static void SaveSfxVolume(float volume);
			static void SaveRanking();
			static void SortRanking();
			static SaveData& GetUserData();
			
			private:
			UserDataManager();
			UserDataManager(const UserDataManager& src) = delete;
			UserDataManager& operator=(const UserDataManager& src) = delete;
			
			static UserDataManager& instance() {
				static UserDataManager inst;
				return inst;
			}
			
			SaveData mSaveData;
			
			// creates some fake data for the initial ranking
			void InitSaveData();
			void SaveUserData();
			void LoadUserData();
	};
	}