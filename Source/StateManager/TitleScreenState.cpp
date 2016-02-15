#include "Common.hpp"
#include "StateManager/TitleScreenState.hpp"
#include "StateManager/StateManager.hpp"
#include "Graphics/Window.hpp"
#include "GUI/Label.hpp"

TitleScreenState::TitleScreenState(StateManager& manager, Context& ctx) noexcept
	: IState{ manager, ctx }
{
	using GUI::Label;

	auto sz{ mContext.window.getSize() };

	// First set up the game title
	mContext.fonts.tryLoad("Prisma", "Resources/Fonts/Prisma.ttf");
	auto gameTitle = std::make_unique<Label>(mContext.fonts.get("Prisma"));
	gameTitle->getText().setCharacterSize(80); 
	gameTitle->setString("Space   Explorer");
	gameTitle->setPosition(sf::Vector2f{ sz / 2u });
	mText[0] = std::move(gameTitle);

	mContext.fonts.tryLoad("Montserrat", "Resources/Fonts/Montserrat.ttf");
	auto infoText = std::make_unique<Label>(mContext.fonts.get("Montserrat"));
	infoText->getText().setCharacterSize(18); 
	infoText->setString("Press any key to continue.");
	infoText->setPosition(sf::Vector2f{
		static_cast<float>(sz.x / 2u), 
		static_cast<float>(sz.y / 2u + 100u) 
	});
	mText[1] = std::move(infoText);

	auto copyrightText = std::make_unique<Label>(mContext.fonts.get("Montserrat"));
	copyrightText->getText().setCharacterSize(12); 
	copyrightText->setString(" Majeri Gabriel 2015");
	copyrightText->setPosition(70.f, sz.y - 10.f);
	mText[2] = std::move(copyrightText);

	mContext.fonts.tryLoad("Arial", "Resources/Fonts/Arial.ttf");
	auto versionText = std::make_unique<Label>(mContext.fonts.get("Arial"));
	versionText->getText().setCharacterSize(14);
	versionText->setString("Version Alpha 1");
	versionText->setPosition(sz.x - 70.f, sz.y - 10.f);
	mText[3] = std::move(versionText);

	mContext.textures.tryLoad("Stars1", "Resources/Textures/Background/Stars.png");
	mContext.textures.get("Stars1").setRepeated(true);
	mBackground.setTexture(mContext.textures.get("Stars1"));
	mBackground.setTextureRect({ 0, 0, 10000, 10000 });
}

TitleScreenState::~TitleScreenState()
{
	mContext.fonts.tryUnload("Prisma");
}

void TitleScreenState::handleEvent(const sf::Event& e) noexcept
{
	if (e.type == e.KeyReleased) {
		mManager.popState();
		if (e.key.code != sf::Keyboard::Escape)
			mManager.pushState(GameState::MainMenu);
	}
	else if (e.type == sf::Event::Resized) {
		auto sz{ mContext.window.getSize() };

		mText[0]->setPosition(sf::Vector2f{ sz / 2u });

		mText[1]->setPosition(sf::Vector2f{
			static_cast<float>(sz.x / 2u),
			static_cast<float>(sz.y / 2u + 100u)
		});

		mText[2]->setPosition(70.f, sz.y - 10.f);

		mText[3]->setPosition(sz.x - 70.f, sz.y - 10.f);
	}
}

void TitleScreenState::update(const sf::Time& dt) noexcept
{
	mAnimationTime = (mAnimationTime + 1) % mMaxTime;
	if (mAnimationTime <= mMaxTime / 2u) 
		mText[1]->scale({ 1 + mZoomSpeed, 1 + mZoomSpeed });
	else
		mText[1]->scale({ 1 - mZoomSpeed, 1 - mZoomSpeed });

}

void TitleScreenState::render(sf::RenderTarget& tgt) const noexcept
{
	tgt.draw(mBackground);

	for (auto& text : mText)
		tgt.draw(*text);
}