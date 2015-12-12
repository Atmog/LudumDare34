#include "PhysicComponent.hpp"
#include "../World.hpp"

namespace ses
{

PhysicComponent::PhysicComponent()
{
    mBody = nullptr;
}

PhysicComponent::~PhysicComponent()
{
    if (mWorld != nullptr && mBody != nullptr)
    {
        mWorld->DestroyBody(mBody);
    }
    mBody = nullptr;
}

void PhysicComponent::init(b2World* world, b2BodyDef* bDef, b2FixtureDef* fDef)
{
    if (world != nullptr)
    {
        mWorld = world;
        mBody = mWorld->CreateBody(bDef);
        mBody->CreateFixture(fDef);
    }
}

void PhysicComponent::setPosition(sf::Vector2f const& position)
{
    if (mBody != nullptr)
    {
        mBody->SetTransform(b2Vec2(Physic::pixelsToMeters(position.x),Physic::pixelsToMeters(position.y)),mBody->GetAngle());
    }
}

sf::Vector2f PhysicComponent::getPosition() const
{
    b2Vec2 p;
    if (mBody != nullptr)
    {
        p = mBody->GetPosition();
    }
    return sf::Vector2f(Physic::metersToPixels(p.x),Physic::metersToPixels(p.y));
}

void PhysicComponent::setRotation(float rotation)
{
    if (mBody != nullptr)
    {
        mBody->SetTransform(mBody->GetPosition(),Physic::degToRad(rotation));
    }
}

float PhysicComponent::getRotation() const
{
    return (mBody != nullptr) ? Physic::radToDeg(mBody->GetAngle()) : 0.f;
}

b2Body* PhysicComponent::getBody()
{
    return mBody;
}

void PhysicComponent::load(pugi::xml_node& node)
{
    if (mEntity != nullptr)
    {
        if (mEntity->getWorld() != nullptr)
        {
            b2BodyDef bDef;
            pugi::xml_node bDefNode = node.child("BodyDef");
            float x,y;
            bDef.type = static_cast<b2BodyType>(bDefNode.attribute("type").as_int());
            x = bDefNode.attribute("pos-x").as_float();
            y = bDefNode.attribute("pos-y").as_float();
            bDef.position.Set(x,y);
            bDef.angle = bDefNode.attribute("angle").as_float();

            b2PolygonShape bShape;
            //pugi::xml_node bShapeNode = node.child("BodyShape");
            bShape.SetAsBox(2,2);

            b2FixtureDef fDef;
            pugi::xml_node fDefNode = node.child("FixtureDef");
            //fDef.density = fDefNode.attribute("density").as_float();
            fDef.density = 5;
            fDef.shape = &bShape;

            init(&mEntity->getWorld()->getSystem<ses::PhysicSystem>().getWorld(),&bDef,&fDef);
        }
    }
}

void PhysicComponent::save(pugi::xml_node& node)
{
    if (mBody != nullptr)
    {
        pugi::xml_node bDefNode = node.append_child("BodyDef");
        bDefNode.append_attribute("type") = mBody->GetType();
        bDefNode.append_attribute("pos-x") = mBody->GetPosition().x;
        bDefNode.append_attribute("pos-y") = mBody->GetPosition().y;
        bDefNode.append_attribute("angle") = mBody->GetAngle();

        pugi::xml_node bShapeNode = node.append_child("BodyShape");

        pugi::xml_node fDefNode = node.append_child("FixtureDef");
    }
}

} // namespace ses
