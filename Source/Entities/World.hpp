#ifndef SES_WORLD_HPP
#define SES_WORLD_HPP

#include <map>
#include <vector>
#include <algorithm>
#include <functional>

#include "Entity.hpp"
#include "System.hpp"

namespace ses
{

class World
{
    public:
        World();
        virtual ~World();

        typedef std::function<Entity::Ptr()> Prefab;

        template <typename ... Args>
        Entity::Ptr getEntity(Args&& ... args);
        template <typename ... Args>
        bool isInstantiated(Args&& ... args);
        template <typename ... Args>
        Entity::Ptr instantiate(Args&& ... args);
        template <typename ... Args>
        void destroy(Args&& ... args);

        template <typename T, typename ... Args>
        T& addSystem(Args ... args);

        template <typename T>
        bool hasSystem();
        bool hasSystem(std::string const& systemId);

        template <typename T>
        T& getSystem();

        template <typename T>
        void removeSystem();
        void removeSystems();

        void update();

        void setPrefab(std::string const& id, Prefab fct);
        Entity::Ptr execPrefab(std::string const& id);
        Entity::Ptr execPrefab(std::string const& id, sf::Vector2f position);

        void handleMessage(sf::Packet& packet);

        EntityVector getEntities() const;
        EntityVector getEntities(ComponentFilter const& filter) const;
        std::size_t getEntitiesCount() const;
        void removeEntities();

        void reset();

    protected:
        EntityVector mEntities;
        std::map<std::string,System::Ptr> mSystems;
        std::map<std::string,Prefab> mPrefabs;
};

template <typename ... Args>
Entity::Ptr World::getEntity(Args&& ... args)
{
    const Id id(std::forward<Args>(args)...);
    auto fct = [&](Entity::Ptr e) -> bool
    {
        if (e == nullptr) { return false; }
        else
        {
            return (e->getId() == id);
        }
    };
    auto itr = std::find_if(mEntities.begin(), mEntities.end(), fct);
    if (itr != mEntities.end())
    {
        return *itr;
    }
    else
    {
        return nullptr;
    }
}

template <typename ... Args>
bool World::isInstantiated(Args&& ... args)
{
    const Id id(std::forward<Args>(args)...);
    auto fct = [&](Entity::Ptr e) -> bool
    {
        if (e == nullptr) { return false; }
        else
        {
            return (e->getId() == id);
        }
    };
    return (std::find_if(mEntities.begin(), mEntities.end(), fct) != mEntities.end());
}

template <typename ... Args>
Entity::Ptr World::instantiate(Args&& ... args)
{
    const Id id(std::forward<Args>(args)...);
    if (!isInstantiated(id))
    {
        mEntities.push_back(std::make_shared<Entity>(id));
    }
    return getEntity(id);
}

template <typename ... Args>
void World::destroy(Args&& ... args)
{
    const Id id(std::forward<Args>(args)...);
    if (isInstantiated(id))
    {
        auto e = getEntity(id);
        if (e != nullptr)
        {
            e->remove();
        }
    }
}

template <typename T, typename ... Args>
T& World::addSystem(Args ... args)
{
    mSystems[lp::type<T>()] = std::make_shared<T>(std::forward<Args>(args)...);
    mSystems[lp::type<T>()]->mWorld = this;
    return getSystem<T>();
}

template <typename T>
bool World::hasSystem()
{
   return mSystems.find(lp::type<T>()) != mSystems.end();
}

template<typename T>
T& World::getSystem()
{
    assert(hasSystem<T>());
    return static_cast<T&>(*mSystems.at(lp::type<T>()));
}

template<typename T>
void World::removeSystem()
{
    auto itr = mSystems.find(lp::type<T>());
    if (itr != mSystems.end())
    {
        itr->second = nullptr;
        mSystems.erase(itr);
    }
}

} // namespace ses

#endif // SES_WORLD_HPP
