#include "Common.hpp"
#include "World/World.hpp"
#include "StateManager/Context.hpp"
#include "EntitySystem/Components/Components.h"
#include "Utilities/MetadataParser.h"

World::World(const std::string& saveName, Context& ctx)
	: mSavePath{ "Saves/" + saveName }, mContext{ ctx }
{
	std::ifstream save{ mSavePath };

	if (save.bad())
		throw new std::runtime_error{ "Could not load saved world " + mSavePath };

	bool first;

	save >> first;

	if (first) {
		save.close();
		loadWorld();
	} else {
		save.close();
		createWorld();
	}
}

void World::handleEvent(const sf::Event& ev) noexcept
{
	
}

void World::update(const sf::Time& dt) noexcept
{
	mManager.update(dt);
}

void World::render(sf::RenderTarget& t) const noexcept
{
	mManager.render(t);
}

void World::loadWorld() noexcept
{
	std::ifstream in{ mSavePath };

	{
		bool t;
		in >> t;
	}

	std::string playerType;
	in >> mPlayerName >> playerType;

	float x, y; 
	in >> x >> y;

	createPlayer(x, y, playerType);

	in.close();
}

void World::createWorld() noexcept
{
	std::ofstream out{ mSavePath };
	out << "1";
	createPlayer(0, 0, "FreighterLight");
	out << "0 0";

	out.close();
}

void World::createPlayer(float x, float y, const std::string& playerType) noexcept
{
	auto& entity = mManager.addEntity();
	entity.addComponent<CTransformable>(sf::Vector2f{ x, y });
	entity.addComponent<CVelocity>();

	mContext.textures.tryLoad(playerType, std::string("Resources/Textures/Ships/") + 
		playerType 
		+ std::string(".png"));

	entity.addComponent<CSprite>(mContext, mContext.textures.get(playerType),
		Metadata::loadTextureMeta(std::string("Resources/Textures/Ships/") + playerType + ".meta"));

	entity.addComponent<CPlayerControl>();

	entity.addGroup(EntityManager::Collisionable);
	entity.addGroup(EntityManager::Drawable);
	mPlayer = &entity;
}