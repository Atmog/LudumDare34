#include "Entity.hpp"

namespace ses
{

Entity::Entity(const Id& id) : mId(id), mNeedRemove(false)
{
}

Entity::~Entity()
{
    removeComponents();
    mNeedRemove = true;
}

const Id& Entity::getId() const
{
    return mId;
}

void Entity::setPositionZ(float z)
{
    mZ = z;
}

float Entity::getPositionZ() const
{
    return mZ;
}

bool Entity::hasComponent(std::string const& componentId)
{
    auto itr = mComponents.find(componentId);
    if (itr != mComponents.end())
    {
        return true;
    }
    return false;
}

bool Entity::hasComponents(ComponentFilter const& filter)
{
    return filter.passFilter(this);
}

void Entity::removeComponents()
{
    mComponents.clear();
}

void Entity::remove()
{
    removeComponents();
    mNeedRemove = true;
}

bool Entity::needRemove() const
{
    return mNeedRemove;
}

} // namespace ses
