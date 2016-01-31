#pragma once
#include "Global.h"

template <typename Resource>
class ResourceHandler {
public:
	// Load a resource from a file
	void loadFromFile(const std::string & id, const std::string & path) {
		// Create a new temp variable to hold the resources
		std::unique_ptr<Resource> res{ new Resource };

		// Try to load the file
		if (res->loadFromFile(path) == false)
			throw new std::runtime_error{ "Could not load " + path };

		// Assume no other resource with this unique ID exists
		assert(mResources[id] == nullptr);

		mResources[id] = std::move(res);
	}

	// Load a resource from a file with an additional parameter passed to the loader
	template <typename Param>
	void loadFromFile(const std::string & id, const std::string & path, const Param & param) {
		auto res{ new Resource };

		if (res->loadFromFile(path, param) == false)
			throw new std::runtime_error{ "Could not load " + path };

		assert(mResources[id] == nullptr);

		mResources[id] = std::move(res);
	}

	Resource & get(const std::string & id)
	{
		auto found = mResources.find(id);
		assert(found != mResources.end());

		return *found->second;
	}

	const Resource & get(const std::string & id) const
	{
		auto found = mResources.find(id);
		assert(found != mResources.end());
		
		return *found->second;
	}

private:
	std::map<std::string, std::unique_ptr<Resource>> mResources;
};

template <>
class ResourceHandler<sf::Music> {
public:
	// Load a resource from a file
	void openFromFile(const std::string & id, const std::string & path) {
		// Create a new temp variable to hold the resources
		std::unique_ptr<sf::Music> res{ new sf::Music };

		// Try to load the file
		if (res->openFromFile(path) == false)
			throw new std::runtime_error{ "Could not load " + path };

		// Assume no other resource with this unique ID exists
		assert(mResources[id] == nullptr);

		mResources[id] = std::move(res);
	}

	sf::Music & get(const std::string & id)
	{
		auto found = mResources.find(id);
		assert(found != mResources.end());

		return *found->second;
	}

	const sf::Music & get(const std::string & id) const
	{
		auto found = mResources.find(id);
		assert(found != mResources.end());

		return *found->second;
	}

private:
	std::map<std::string, std::unique_ptr<sf::Music>> mResources;
};

using TextureHandler = ResourceHandler<sf::Texture>; 
using MusicHandler = ResourceHandler<sf::Music>;