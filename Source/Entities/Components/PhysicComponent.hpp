#ifndef SES_PHYSICCOMPONENT_HPP
#define SES_PHYSICCOMPONENT_HPP

#include "../Component.hpp"
#include "../Systems/PhysicSystem.hpp"

namespace ses
{

class PhysicComponent : public Component
{
    public:
        PhysicComponent(b2World& world, b2BodyDef const& bDef, b2FixtureDef const& fDef);
        virtual ~PhysicComponent();

        void setPosition(sf::Vector2f const& position);
        sf::Vector2f getPosition() const;

        void setRotation(float rotation);
        float getRotation() const;

        b2Body* getBody();

    protected:
        b2World& mWorld;
        b2Body* mBody;
};

} // namespace ses

#endif // SES_PHYSICCOMPONENT_HPP
