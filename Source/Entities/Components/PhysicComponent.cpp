#include "PhysicComponent.hpp"

namespace ses
{

PhysicComponent::PhysicComponent()
: mMass(0.f)
{
}

PhysicComponent::PhysicComponent(float mass)
: mMass(mass)
{
}

PhysicComponent::~PhysicComponent()
{
}


} // namespace ses
