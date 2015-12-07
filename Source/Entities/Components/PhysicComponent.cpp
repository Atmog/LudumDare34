#include "PhysicComponent.hpp"
#include <iostream>

namespace ses
{

PhysicComponent::PhysicComponent(b2World& world, b2BodyDef const& bDef, b2FixtureDef const& fDef)
: mWorld(world)
{
    mBody = mWorld.CreateBody(&bDef);
    mBody->CreateFixture(&fDef);
}

PhysicComponent::~PhysicComponent()
{
    mWorld.DestroyBody(mBody);
}

void PhysicComponent::setPosition(sf::Vector2f const& position)
{
    mBody->SetTransform(b2Vec2(Physic::pixelsToMeters(position.x),Physic::pixelsToMeters(position.y)),mBody->GetAngle());
}

sf::Vector2f PhysicComponent::getPosition() const
{
    b2Vec2 p = mBody->GetPosition();
    return sf::Vector2f(Physic::metersToPixels(p.x),Physic::metersToPixels(p.y));
}

void PhysicComponent::setRotation(float rotation)
{
    mBody->SetTransform(mBody->GetPosition(),Physic::degToRad(rotation));
}

float PhysicComponent::getRotation() const
{
    return Physic::radToDeg(mBody->GetAngle());
}

b2Body* PhysicComponent::getBody()
{
    return mBody;
}

} // namespace ses
