#pragma once
#include "Common.hpp"
#include "Component.hpp"

namespace GUI {
class Container final : public Component {
public:
	explicit Container() = default;
	~Container() = default;

	void addChild(ComponentPtr component);

	bool isSelectable() const noexcept override;
	void handleEvent(const sf::Event& e) noexcept override;

	ComponentPtr& getChild(size_t i) noexcept;
private:
	void draw(sf::RenderTarget& t, sf::RenderStates states) const noexcept override;

	bool hasSelection() const noexcept;

	void select(size_t i) noexcept;
	void selectNext() noexcept;
	void selectPrevious() noexcept;

	std::vector<ComponentPtr> mChildren{};
	int mSelectedChild{ -1 };
};
}