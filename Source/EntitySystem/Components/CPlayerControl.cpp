#include "Common.hpp"
#include "EntitySystem/Components/CPlayerControl.hpp"

void CPlayerControl::init() noexcept
{
	mSpriteComponent = &mOwner->getComponent<CSprite>();
	mTransformableComponent = mSpriteComponent->mTransformableComponent;
}

void CPlayerControl::update(const sf::Time& dt) noexcept
{
	auto cs{ cos(mSpriteComponent->mRotation) },
		sn{ sin(mSpriteComponent->mRotation) };

	using sf::Keyboard;
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		mSpriteComponent->mVelocityComponent->mVelocity = 
			sf::Vector2f{ cs * 100.f, sn * 100.f };
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		mSpriteComponent->mVelocityComponent->mVelocity =
			sf::Vector2f{ -cs * 100.f, -sn * 100.f };
	}
	else {
		mSpriteComponent->mVelocityComponent->mVelocity = { 0.f, 0.f };
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		mTransformableComponent->rotate(-1);
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		mTransformableComponent->rotate(+1);
	}
}

void CPlayerControl::render(sf::RenderTarget& t) const noexcept
{

}