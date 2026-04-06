#include <algorithm>
#include "RenderManager.hpp"

#include <iostream>

namespace pyramidnight {
	
	RenderManager::RenderManager() :
		mWindow(sf::VideoMode(RNDR_RESOLUTION),
		"PyraMidNight",
		sf::Style::Titlebar | sf::Style::Close) {
			mWindow.setFramerateLimit(RNDR_FRAME_LIMIT);
	}
	
	void RenderManager::Init() { instance(); }

	void RenderManager::Update(std::vector<std::shared_ptr<sf::Drawable>>& drawables) {
		instance().Draw(drawables);
		instance().DrawEffects();
	}

	void RenderManager::Draw(std::vector<std::shared_ptr<sf::Drawable>> &drawables) {
		mWindow.clear();
		for (const auto &drw : drawables)
			mWindow.draw(*drw);
		mWindow.display();
	}

	void RenderManager::DrawEffects() {
		if (!mRenderEffects.empty()) {
			for (auto& eff : mRenderEffects) {
				eff->Update();
			};

			mRenderEffects.erase(std::remove_if(mRenderEffects.begin(), mRenderEffects.end(),
				[](const std::unique_ptr<RenderEffect>& eff) {
					return eff->Duration <= 0.0f;
				}),
			mRenderEffects.end()
			);
		}
	}

	void RenderManager::DisplayEffect(std::unique_ptr<RenderEffect> effect) {
		instance().mRenderEffects.push_back(std::move(effect));
	}

	sf::Time& RenderManager::GetDeltaTime() { 
		auto& deltaTime = instance().mDeltaTime;
		auto& clock = instance().mClock;
		
		deltaTime = clock.restart();
		return deltaTime;
	}
	
	sf::RenderWindow& RenderManager::GetWindow() { return instance().mWindow; }
}	
