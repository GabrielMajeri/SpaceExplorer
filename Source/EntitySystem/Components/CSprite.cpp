#include "Common.hpp"
#include "EntitySystem/Components/CSprite.hpp"
#include "Base/Game.hpp"

CSprite::CSprite(Context& ctx, const sf::Texture& tex, Metadata::TextureMeta texMeta) noexcept
	: mContext{ ctx }, mView{ mContext.window.getView() }, mTextureMeta( texMeta ),
	mSprite { tex, mTextureMeta.parts[0] }
{
	mSprite.setOrigin(mTextureMeta.parts[0].width / 2.f, mTextureMeta.parts[0].height / 2.f);
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