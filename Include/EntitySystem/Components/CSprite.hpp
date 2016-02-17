#pragma once
#include "Common.hpp"
#include "Base/Game.hpp"
#include "StateManager/Context.hpp"
#include "EntitySystem/Component.hpp"
#include "EntitySystem/Components/CTransformable.hpp"
#include "EntitySystem/Components/CVelocity.hpp"
#include "Utilities/MetadataParser.h"

class CSprite final : public Component {
public:
	explicit CSprite(Context& ctx, const sf::Texture& tex, Metadata::TextureMeta texMeta) noexcept;
	~CSprite() = default;

	void init() noexcept override;
	void update(const sf::Time& dt) noexcept override;
	void render(sf::RenderTarget& t) const noexcept override;

	const sf::FloatRect getGlobalBounds() const noexcept;

	Context& mContext;
	const sf::View& mView;
	Metadata::TextureMeta mTextureMeta; 
	sf::Sprite mSprite;
	float mRotation{ 0.f };

	CTransformable* mTransformableComponent{ nullptr };
	CVelocity* mVelocityComponent{ nullptr };
};