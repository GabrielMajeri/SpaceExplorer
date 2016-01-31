#include "World/World.h"

#include "Player/Player.h"

World::World(Window & w, bool * keys)
	: mKeys{ keys },
	mView{ {w.getWidth() / 2.f, w.getHeight() / 2.f}, { (float)w.getWidth(), (float)w.getHeight() } },
	mWindow{ w }
{
	loadAll();

	mEntities.emplace_back(EntityPtr{
		new Player{ *this, mKeys,
					Spaceship{ {400, 300},
						mTextures.get("ship1"),
						mTextures.get("missile1")
					} 
	} });
	mView.zoom(1);
}

void World::update(const sf::Time & dt)
{
	for (auto & entity : mEntities)
		entity->update(dt);
}

void World::draw(sf::RenderTarget & t)
{
	t.setView(mView);

	t.draw(mBackground);

	for (auto & entity : mEntities)
		entity->draw(t);
}

sf::View & World::getView()
{
	return mView;
}

Window & World::getWindow()
{
	return mWindow;
}

void World::loadAll()
{
	mTextures.loadFromFile("ship1", "Resources/Textures/spaceship1.png");
	mTextures.loadFromFile("missile1", "Resources/Textures/missile1.png");
	mTextures.loadFromFile("stars", "Resources/Textures/background.png");
	mBackground.setTexture(mTextures.get("stars"));
	mBackground.setTextureRect({ 0, 0, 192000, 108000 });
	mBackground.setOrigin(192000.f / 2, 108000.f / 2);
	mTextures.get("stars").setRepeated(true);

	mMusic.openFromFile("bgm1", "Resources/Music/CamelopardalisStretched.ogg");
	mMusic.get("bgm1").play();
}
