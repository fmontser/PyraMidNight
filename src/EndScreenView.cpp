#include "EndScreenView.hpp"
#include "Game.hpp"

constexpr std::string_view TITLE_STR = "GAME OVER!";
constexpr std::string_view CONTINUE_STR = "Press SPACE to continue!";
constexpr std::string_view ABC_STR = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//TODO hardcoded values
EndScreenView::EndScreenView() : ScreenView() {
	mIsRankingDraw = false;
	mIsNameSet =  false;

	//TODO filesystem exception control
	mFont = std::make_shared<sf::Font>("assets/ClearSans-Regular.ttf");

	mTitleTxt = std::make_shared<sf::Text>(*mFont);
	mTitleTxt->setString(std::string(TITLE_STR));
	mTitleTxt->setCharacterSize(80);
	mTitleTxt->setFillColor(sf::Color::Blue);
	mTitleTxt->setPosition({100.f, 100.f});
	mTitleTxt->setOutlineColor(sf::Color::Yellow);
	mTitleTxt->setOutlineThickness(4);

	//TODO make dynamic score ranking
	auto rankingEntryPos = sf::Vector2f({100.0f, 160.0f});
	for (size_t i = 0; i < 10; i++) {
		auto nameEntry = std::make_shared<sf::Text>(*mFont);
		nameEntry->setString("AAA");
		auto textOffset = sf::Vector2f({160.0f, 40.0f});

		rankingEntryPos.y += textOffset.y;
		nameEntry->setCharacterSize(48);
		nameEntry->setFillColor(sf::Color::White);
		nameEntry->setPosition(rankingEntryPos);
		nameEntry->setOutlineColor(sf::Color::Blue);
		nameEntry->setOutlineThickness(1);

		auto scoreEntry = std::make_shared<sf::Text>(*mFont);
		scoreEntry->setString("0000000000");

		rankingEntryPos.x += textOffset.x;
		scoreEntry->setCharacterSize(48);
		scoreEntry->setFillColor(sf::Color::White);
		scoreEntry->setPosition(rankingEntryPos);
		scoreEntry->setOutlineColor(sf::Color::Blue);
		scoreEntry->setOutlineThickness(1);
		rankingEntryPos.x -= textOffset.x;

		mRankingTxt.push_back({nameEntry, scoreEntry});
	}
	
	mStartTxt = std::make_shared<sf::Text>(*mFont);
	mStartTxt->setString(std::string(CONTINUE_STR));
	mStartTxt->setCharacterSize(40);
	mStartTxt->setFillColor(sf::Color::Blue);
	mStartTxt->setPosition({100.f, 650.f});
	mStartTxt->setOutlineColor(sf::Color::Yellow);
	mStartTxt->setOutlineThickness(3);

	mBackgroundTex = std::make_shared<sf::Texture>(sf::Texture("assets/Background.png"));
	mBackground = std::make_shared<sf::Sprite>(sf::Sprite(*mBackgroundTex));
	mBackground->setColor({64, 0, 0, 255});

	mCursor = CreateCursor();

	mDrawables.push_back(mBackground);
	mDrawables.push_back(mTitleTxt);
	mDrawables.push_back(mStartTxt);

	for (const auto& entry : mRankingTxt) {
		mDrawables.push_back(entry.name);
		mDrawables.push_back(entry.score);
	}

	mDrawables.push_back(mCursor);
}

void EndScreenView::Update(Game& game) {
	auto& frameInput = game.GetInputManager().FetchInput();
	auto& deltaTime = game.GetRenderManager().GetDeltaTime();
	auto& window = game.GetRenderManager().GetWindow();

	if (frameInput.close)
		window.close();

	if (frameInput.action)
		game.SetState(Game::State::TITLE_SCREEN);

	if (!mIsRankingDraw)
		mIsRankingDraw = ShowRanking(game);
	else if (!mIsNameSet) {
		mIsNameSet = EnterRecordName(game, frameInput);
	}
}

bool EndScreenView::ShowRanking(Game& game) {
	auto ranking = game.GetRanking();
	size_t i = 0;

	for (auto& gameEntry : ranking) {
		if (i < mRankingTxt.size()) {
			mRankingTxt[i].name->setString(gameEntry.name);
			mRankingTxt[i].score->setString(PadZeroScore(gameEntry.score, 10));
		}
		i++;
	}
	return true;
}

std::shared_ptr<sf::RectangleShape>& EndScreenView::CreateCursor() {
	auto cursorSize =  sf::Vector2f({});
	auto cursor = std::make_shared<sf::RectangleShape>(sf::RectangleShape());

	cursorSize.x =	mFont->getGlyph('?', 48.0f, false).bounds.size.x;
	cursorSize.y =	mFont->getGlyph('?', 48.0f, false).bounds.size.y;

	cursor->setSize(cursorSize);
	cursor->setFillColor({0, 0, 0, 0});
	cursor->setOutlineColor({0, 255, 0, 255});
	cursor->setOutlineThickness(2);
	return cursor;
}

std::string EndScreenView::PadZeroScore(uint32_t score, uint32_t digits) {
	std::ostringstream ss;

	ss << std::setw(digits) << std::setfill('0') << score;
	return ss.str();
}
