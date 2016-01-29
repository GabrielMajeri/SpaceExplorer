template <typename Res, typename ID>
void ResourceManager<Res, ID>::loadFromFile(const ID & id, const std::string & path)
{
    std::unique_ptr<Res> resource{new Res{ }};

    if(resource->loadFromFile(path) == false)
        throw new std::runtime_error{ "Cannot load file: " + path };

    auto insertResult = mResourceMap.insert(std::make_pair(id, std::move(resource)));

    assert(insertResult.second);
}

template <typename Res, typename ID>
template <typename Parameter>
void ResourceManager<Res, ID>::loadFromFile(const ID & id, const std::string & path, const Parameter & p)
{
    std::unique_ptr<Res> resource{new Res{ }};

    if(resource->loadFromFile(path, p) == false)
        throw new std::runtime_error{ "Cannot load file: " + path };

    auto insertResult = mResourceMap.insert(std::make_pair(id, std::move(resource)));

    assert(insertResult.second);
}


template <typename Res, typename ID>
Res & ResourceManager<Res, ID>::getResource(const ID & id)
{
    auto res = mResourceMap.find(id);

    assert(res != mResourceMap.end());

    return *res->second;
}

template <typename Res, typename ID>
const Res & ResourceManager<Res, ID>::getResource(const ID & id) const
{
    auto res = mResourceMap.find(id);

    assert(res != mResourceMap.end());

    return *res->second;
}

template <typename Res, typename ID>
void ResourceManager<Res, ID>::create(const unsigned int & width, const unsigned int & height, const ID & id)
{
    std::unique_ptr<Res> resource{new Res{ }};

    if(resource->create(width, height) == false)
        throw new std::runtime_error{ "Cannot create texture." };

    auto insertResult = mResourceMap.insert(std::make_pair(id, std::move(resource)));

    assert(insertResult.second);
}
