#pragma once
#include "Common.hpp"

template <typename R>
class ResourceHandler : private NonCopyable {
public:
	explicit ResourceHandler() noexcept = default;

	void load(const std::string& id, const std::string& path);
	void tryLoad(const std::string& id, const std::string& path);

	void unload(const std::string& id);
	void tryUnload(const std::string& id);

	R& get(const std::string& id);

private:
	std::unordered_map<std::string, std::unique_ptr<R>> mMap{ };

};

#include "ResourceHandler.inl"

using TextureHandler = ResourceHandler<sf::Texture>;
using FontHandler = ResourceHandler<sf::Font>;
