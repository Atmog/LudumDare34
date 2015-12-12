#include "PhysicSystem.hpp"
#include "../World.hpp"
#include "../Components.hpp"

namespace ses
{

PhysicSystem::PhysicSystem()
{
    mFilter.requires(lp::type<PhysicComponent>());
    mPhysicWorld = new b2World(b2Vec2(0.f,0.f));
}

PhysicSystem::~PhysicSystem()
{
}

void PhysicSystem::setGravity(sf::Vector2f const& gravity)
{
    mPhysicWorld->SetGravity(b2Vec2(gravity.x,gravity.y));
}

sf::Vector2f PhysicSystem::getGravity() const
{
    b2Vec2 g = mPhysicWorld->GetGravity();
    return sf::Vector2f(g.x,g.y);
}

b2World& PhysicSystem::getWorld()
{
    return *mPhysicWorld;
}

void PhysicSystem::update(sf::Time dt)
{
    if (!mWorld)
    {
        return;
    }

    // Update the body position
    auto e = mWorld->getEntities(mFilter);
    /*for (std::size_t i = 0; i < e.size(); i++)
    {
        auto p = e[i]->getComponent<PhysicComponent>();
        p.setPosition(e[i]->getPosition());
        p.setRotation(e[i]->getRotation());
    }*/

    // World Step
    mPhysicWorld->Step(dt.asSeconds(),8,3);

    // Update the entity position
    for (std::size_t i = 0; i < e.size(); i++)
    {
        ses::PhysicComponent& p = e[i]->getComponent<PhysicComponent>();
        e[i]->setPosition(p.getPosition());
        e[i]->setRotation(p.getRotation());
    }
}

} // namespace ses
