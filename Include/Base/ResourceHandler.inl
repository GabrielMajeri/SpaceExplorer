#include "ResourceHandler.hpp"
#include "ResourceHandler.hpp"
#include "ResourceHandler.hpp"
#pragma once

template<typename R>
inline void ResourceHandler<R>::load(const std::string& id, const std::string& path)
{
	auto ptr = std::make_unique<R>();

	if (!ptr->loadFromFile(path))
		throw std::runtime_error{ "Could not load file " + path };

	assert(mMap.count(id) == 0);

	mMap[id] = std::move(ptr);
}

template<typename R>
inline void ResourceHandler<R>::tryLoad(const std::string & id, const std::string & path)
{
	if (mMap.count(id))
		return;
	
	load(id, path);
}

template<typename R>
inline void ResourceHandler<R>::unload(const std::string& id)
{
	assert(mMap.count(id));

	mMap.erase(id);
}

template<typename R>
inline void ResourceHandler<R>::tryUnload(const std::string & id)
{
	if (!mMap.count(id))
		return;
	unload(id);
}

template<typename R>
inline R& ResourceHandler<R>::get(const std::string& id)
{
	assert(mMap.count(id));
	return *mMap[id];
}