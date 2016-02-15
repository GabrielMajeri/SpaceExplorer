#include "Common.hpp"
#include "GUI/Container.hpp"

bool GUI::Container::isSelectable() const noexcept
{
	return false;
}

void GUI::Container::handleEvent(const sf::Event& e) noexcept
{
	if (hasSelection() && mChildren[mSelectedChild]->isActive())
		mChildren[mSelectedChild]->handleEvent(e);
	else if (e.type == sf::Event::KeyReleased) 
		switch (e.key.code) {
		case sf::Keyboard::W: case sf::Keyboard::Up:
			selectPrevious();
			break;
		case sf::Keyboard::S: case sf::Keyboard::Down:
			selectNext();
			break;
		case sf::Keyboard::Return: case sf::Keyboard::Space:
			if (hasSelection())
				mChildren[mSelectedChild]->setActive(true);
			break;
		}
}

void GUI::Container::draw(sf::RenderTarget& t, sf::RenderStates states) const noexcept
{
	states.transform.combine(getTransform());

	for (const auto& child : mChildren)
		t.draw(*child, states);
}

void GUI::Container::addChild(ComponentPtr component)
{
	mChildren.push_back(std::move(component));

	if (!hasSelection() && mChildren.back()->isSelectable())
		select(mChildren.size() - 1);
}

GUI::Container::ComponentPtr& GUI::Container::getChild(size_t i) noexcept
{
	assert(i < mChildren.size());
	return mChildren[i];
}

bool GUI::Container::hasSelection() const noexcept
{
	return 0 <= mSelectedChild;
}

void GUI::Container::select(size_t i) noexcept
{
	assert(mChildren.size() > i);
	if (mChildren[i]->isSelectable()) {
		if (hasSelection())
			mChildren[mSelectedChild]->setSelected(false);

		mChildren[i]->setSelected(true);
		mSelectedChild = i;
	}
}

void GUI::Container::selectNext() noexcept
{
	if (!hasSelection())
		return;

	auto next{ mSelectedChild };

	do next = (next + 1) % mChildren.size();
	while (!mChildren[next]->isSelectable());

	select(next);
}

void GUI::Container::selectPrevious() noexcept
{
	if (!hasSelection())
		return;

	auto prev{ mSelectedChild };

	do prev = (prev + mChildren.size() - 1) % mChildren.size();
	while (!mChildren[prev]->isSelectable());

	select(prev);
}
