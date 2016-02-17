#pragma once
#include "Common.hpp"
#include "EntitySystem/EntityManager.hpp"

struct Context;

class World : private NonCopyable {
public:
	World(const std::string& saveName, Context& ctx);

	void handleEvent(const sf::Event& ev) noexcept;
	void update(const sf::Time& dt) noexcept;
	void render(sf::RenderTarget& t) const noexcept;

private:
	void loadWorld() noexcept;
	void createWorld() noexcept;

	void createPlayer(float x, float y, const std::string& playerType) noexcept;

	const std::string mSavePath;
	Context& mContext;

	EntityManager mManager;
	std::string mPlayerName;
	Entity* mPlayer;
};