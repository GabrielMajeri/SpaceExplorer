#pragma once
#include "Common.hpp"
#include "CSprite.hpp"

class CPlayerControl : public Component {
public:

	void init() noexcept override;
	void update(const sf::Time& dt) noexcept override;
	void render(sf::RenderTarget& t) const noexcept override;

	CSprite* mSpriteComponent{ nullptr };
	CTransformable* mTransformableComponent{ nullptr };
};