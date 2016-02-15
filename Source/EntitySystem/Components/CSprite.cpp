#include "Common.hpp"
#include "EntitySystem/Components/CSprite.hpp"
#include "Base/Game.hpp"

CSprite::CSprite(Context& ctx, const sf::Texture& tex, const sf::IntRect& texRect) noexcept
	: mContext{ ctx }, mView{ mContext.window.getView() }, mSprite{ tex, texRect }
{
	mSprite.setOrigin(texRect.width / 2.f, texRect.height / 2.f);
}

const sf::FloatRect CSprite::getGlobalBounds() const noexcept
{
	return mTransformableComponent->getTransform().transformRect(mSprite.getLocalBounds());
}

void CSprite::init() noexcept
{
	mTransformableComponent = &mOwner->getComponent<CTransformable>();
	mVelocityComponent = &mOwner->getComponent<CVelocity>();
}

void CSprite::update(const sf::Time& dt) noexcept
{
	mRotation = toRadians(mTransformableComponent->getRotation());
}

void CSprite::render(sf::RenderTarget& t) const noexcept
{
	if (isVisible(mView, getGlobalBounds()))
		t.draw(mSprite, mTransformableComponent->getTransform());
}