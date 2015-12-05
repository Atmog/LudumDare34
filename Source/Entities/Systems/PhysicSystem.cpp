#include "PhysicSystem.hpp"
#include "../World.hpp"

namespace ses
{

PhysicSystem::PhysicSystem()
{
    mFilter.requires(type<PhysicComponent>());
}

PhysicSystem::~PhysicSystem()
{
}

void PhysicSystem::update(sf::Time dt)
{
    if (!mWorld)
    {
        return;
    }

    auto e = mWorld->getEntities(mFilter);

}

} // namespace ses
