#include <algorithm>
#include "RenderManager.hpp"

namespace pyramidnight {
	
	RenderManager::RenderManager() :
		mWindow(sf::VideoMode(RNDR_RESOLUTION),
		"PyraMidNight",
		sf::Style::Titlebar | sf::Style::Close) {
			mWindow.setFramerateLimit(RNDR_FRAME_LIMIT);
	}
	
	void RenderManager::Init() { instance(); }

	void RenderManager::Update(std::vector<std::shared_ptr<sf::Drawable>>& drawables) {
		instance().mDeltaTime = instance().mClock.restart();

		instance().Draw(drawables);
	}

	void RenderManager::PauseClock() { instance().mClock.stop(); }

	void RenderManager::ResumeClock() { instance().mClock.start(); }

	void RenderManager::Draw(std::vector<std::shared_ptr<sf::Drawable>> &drawables) {
		mWindow.clear();
		DrawEffects();
		for (const auto &drw : drawables) {
			mWindow.draw(*drw);
		}
		mWindow.display();
	}

	void RenderManager::DrawEffects() {
		if (!mRenderEffects.empty()) {
			for (auto& eff : mRenderEffects) {
				eff->Update({mDeltaTime, mWindow});
			};

			mRenderEffects.erase(std::remove_if(mRenderEffects.begin(), mRenderEffects.end(),
				[](const std::unique_ptr<RenderEffect>& eff) {
					return eff->Disposable;
				}),
			mRenderEffects.end()
			);
		}
	}

	void RenderManager::DisplayEffect(std::unique_ptr<RenderEffect> effect) {
		instance().mRenderEffects.push_back(std::move(effect));
	}

	sf::Time& RenderManager::GetDeltaTime() { return instance().mDeltaTime; }
	
	sf::RenderWindow& RenderManager::GetWindow() { return instance().mWindow; }
}	
