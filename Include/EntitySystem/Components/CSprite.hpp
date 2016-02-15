#pragma once
#include "Common.hpp"
#include "Base/Game.hpp"
#include "StateManager/Context.hpp"
#include "EntitySystem/Component.hpp"
#include "EntitySystem/Components/CTransformable.hpp"
#include "EntitySystem/Components/CVelocity.hpp"

class CSprite final : public Component {
public:
	explicit CSprite(Context& ctx, const sf::Texture& tex, const sf::IntRect& texRect) noexcept;
	~CSprite() = default;

	void init() noexcept override;
	void update(const sf::Time& dt) noexcept override;
	void render(sf::RenderTarget& t) const noexcept override;

	const sf::FloatRect getGlobalBounds() const noexcept;

	Context& mContext;
	const sf::View& mView;
	sf::Sprite mSprite;
	float mRotation{ 0.f };

	CTransformable* mTransformableComponent{ nullptr };
	CVelocity* mVelocityComponent{ nullptr };
};