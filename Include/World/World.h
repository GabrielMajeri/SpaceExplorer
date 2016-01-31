#pragma once
#include "Global.h"

#include "GameEntity.h"
#include "Graphics/Window.h"
#include "ResourceHandler.h"

class World {
public:
	World(Window & w, bool * keys);

	void update(const sf::Time & dt);
	void draw(sf::RenderTarget & t);

	sf::View & getView();
	Window & getWindow();

	TextureHandler mTextures;
	MusicHandler mMusic;
private:
	//	TODO: remove
	sf::Sprite mBackground;
	//

	void loadAll();

	bool * mKeys;
	
	sf::View mView;

	Window & mWindow;

	std::vector<EntityPtr> mEntities;
};