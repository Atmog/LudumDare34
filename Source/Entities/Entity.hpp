#ifndef SES_ENTITY_HPP
#define SES_ENTITY_HPP

#include <map>
#include <memory>
#include <string>
#include <cassert>

#include <SFML/Graphics/Transformable.hpp>

#include "Component.hpp"
#include "ComponentFilter.hpp"
#include "Id.hpp"

#include "../Helper/TypeToString.hpp"

namespace ses
{

class Entity : public sf::Transformable
{
    public:
        Entity(const Id& id);
        virtual ~Entity();

        typedef std::shared_ptr<Entity> Ptr;

        const Id& getId() const;

        void setPositionZ(float z);
        float getPositionZ() const;

        template<typename T, typename ... Args>
        T& addComponent(Args&& ... args);

        template<typename T>
        bool hasComponent();
        bool hasComponent(std::string const& componentId);
        bool hasComponents(ComponentFilter const& filter);

        template<typename T>
        T& getComponent();

        template<typename T>
        void removeComponent();
        void removeComponents();

        void remove();
        bool needRemove() const;

    protected:
        const Id mId;
        std::map<std::string,Component::Ptr> mComponents;
        float mZ;
        bool mNeedRemove;
};

template<typename T, typename ... Args>
T& Entity::addComponent(Args&& ... args)
{
    mComponents[lp::type<T>()] = std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    mComponents[lp::type<T>()]->mEntity = this;
    return getComponent<T>();
}

template<typename T>
bool Entity::hasComponent()
{
    return hasComponent(lp::type<T>());
}

template<typename T>
T& Entity::getComponent()
{
    assert(hasComponent<T>());
    return static_cast<T&>(*mComponents.at(lp::type<T>()));
}

template<typename T>
void Entity::removeComponent()
{
    auto itr = mComponents.find(lp::type<T>());
    if (itr != mComponents.end())
    {
        itr->mEntity = nullptr;
        mComponents.erase(itr);
    }
}

typedef std::vector<Entity::Ptr> EntityVector;

} // namespace ses

#endif // SES_ENTITY_HPP
