#pragma once

#include <map>
#include <memory>
#include <cassert>

template <typename Resource, typename ID>
class ResourceManager
{
public:
    void loadFromFile(const ID & id, const std::string & path);

    template <typename Parameter>
    void loadFromFile(const ID & id, const std::string & path, const Parameter & p);

    Resource & getResource(const ID & id);
    const Resource & getResource(const ID & id) const;

    // This is for textures only
    void create(const unsigned int & width, const unsigned int & height, const ID & id);

private:
    std::map<ID, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceManager.inl"
