#include "World.hpp"

namespace ses
{

World::World()
{
}

World::~World()
{
    reset();
}

bool World::hasSystem(std::string const& systemId)
{
    return mSystems.find(systemId) != mSystems.end();
}

void World::removeSystems()
{
    mSystems.clear();
}

void World::update()
{
    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i] == nullptr)
        {
            mEntities.erase(mEntities.begin() + i);
        }
        else
        {
            if (mEntities[i]->needRemove())
            {
                mEntities.erase(mEntities.begin() + i);
            }
        }
    }
}

void World::setPrefab(std::string const& id, Prefab prefab)
{
    mPrefabs[id] = prefab;
}

Entity::Ptr World::execPrefab(std::string const& id)
{
    if (mPrefabs.find(id) != mPrefabs.end())
    {
        if (mPrefabs.at(id))
        {
            return mPrefabs.at(id)();
        }
    }
    return nullptr;
}

Entity::Ptr World::execPrefab(std::string const& id, sf::Vector2f position)
{
    auto e = execPrefab(id);
    if (e != nullptr)
    {
        e->setPosition(position);
    }
    return e;
}

void World::handleMessage(sf::Packet& packet)
{
    std::string type;
    packet >> type;

    if (hasSystem(type))
    {
        mSystems.at(type)->handleMessage(packet);
    }
}

EntityVector World::getEntities() const
{
    return mEntities;
}

EntityVector World::getEntities(ComponentFilter const& filter) const
{
    EntityVector v;
    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        if (filter.passFilter(mEntities[i].get()))
        {
            v.push_back(mEntities[i]);
        }
    }
    return v;
}

std::size_t World::getEntitiesCount() const
{
    return mEntities.size();
}

void World::removeEntities()
{
    mEntities.clear();
}

void World::reset()
{
    removeSystems();
    removeEntities();
}

} // namespace ses
