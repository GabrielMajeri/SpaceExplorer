template <typename R>
void ResourceHolder<R>::clear() noexcept
{
	resources.clear();
}

template <typename R>
bool ResourceHolder<R>::exists(const std::string& id) noexcept
{
	return resources.count(id) != 0;
}

template <typename R>
void ResourceHolder<R>::load(const std::string& id, const std::string& path)
{
	if(exists(id))
		return;

	auto resPtr = std::make_unique<R>();

	if(!resPtr->loadFromFile(path))
		throw std::runtime_error{ "[RESOURCES] Could not load file " + path };

	resources[id] = std::move(resPtr);
}

template <typename R>
template <typename P>
void ResourceHolder<R>::load(const std::string& id, const std::string& path, const P& param)
{
	if(exists(id))
		return;

	auto resPtr = std::make_unique<R>();

	if(!resPtr->loadFromFile(path, param))
		throw std::runtime_error{ "[RESOURCES] Could not load file " + path };

	resources[id] = std::move(resPtr);
}

template <typename R>
void ResourceHolder<R>::unload(const std::string& id) noexcept
{
	if(resources.count(id) == 0)
		return;

	resources.erase(id);
}

template <typename R>
R& ResourceHolder<R>::operator[](const std::string& id)
{
	return *resources[id];
}

template <typename R>
const R& ResourceHolder<R>::operator[](const std::string& id) const
{
	return *resources.at(id);
}
