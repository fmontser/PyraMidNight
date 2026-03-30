#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"

namespace fknd {
	
	class ResourceManager {
		public:
			ResourceManager();
		private:
			void ValidateLevels();
	};

}