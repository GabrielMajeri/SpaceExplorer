#pragma once

#include <unordered_map>
#include <memory>

template <typename R>
class ResourceHolder
{
public:
	void clear() noexcept;

    bool exists(const std::string& id) noexcept;

    void load(const std::string& id, const std::string& path) noexcept;

    template <typename P>
    void load(const std::string& id, const std::string& path, const P& param) noexcept;

    void unload(const std::string& id) noexcept;

    R& operator[](const std::string& id);
    const R& operator[](const std::string& id) const;
private:
	std::unordered_map<std::string, std::unique_ptr<R>> resources;
};

#include "Utility/ResourceHolder.inl"

#include <SFML/Graphics/Texture.hpp>
using TextureHolder = ResourceHolder<sf::Texture>;

#include <SFML/Graphics/Font.hpp>
using FontHolder = ResourceHolder<sf::Font>;

#include <SFML/Graphics/Shader.hpp>
using ShaderHolder = ResourceHolder<sf::Shader>;
