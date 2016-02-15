#include "Common.hpp"
#include "StateManager/PlayingState.hpp"
#include "StateManager/Context.hpp"
#include "EntitySystem/Component.hpp"
#include "EntitySystem/Components/CTransformable.hpp"
#include "EntitySystem/Components/CSprite.hpp"
#include "EntitySystem/Components/CPlayerControl.hpp"

PlayingState::PlayingState(StateManager & manager, Context & ctx) noexcept
	: IState{ manager, ctx }
{
	mContext.textures.load("FreighterLight", 
		"Resources/Textures/Ships/Freighters/FreighterLight.png");

	auto& player{ mEntities.addEntity() };

	player.addComponent<CTransformable>(sf::Vector2f{ 150, 150 });
	player.addComponent<CVelocity>();
	player.addComponent<CSprite>(mContext, mContext.textures.get("FreighterLight"), 
								 sf::IntRect{ 0, 0, 56, 54 });
	player.addComponent<CPlayerControl>();
	player.addGroup(EntityManager::EntityGroup::Drawable);

	mContext.textures.tryLoad("Stars1", "Resources/Textures/Background/Stars.png"); 
	mContext.textures.get("Stars1").setRepeated(true);
}

PlayingState::~PlayingState()
{
	mContext.textures.tryUnload("FreighterLight");
	mContext.textures.tryUnload("Stars1");
}

void PlayingState::handleEvent(const sf::Event& e) noexcept
{

}

void PlayingState::update(const sf::Time& dt) noexcept
{
	mEntities.cleanup();
	mEntities.update(dt);
}

void PlayingState::render(sf::RenderTarget& t) const noexcept
{
	mEntities.render(t);
}