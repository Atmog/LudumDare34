#ifndef SES_PHYSICCOMPONENT_HPP
#define SES_PHYSICCOMPONENT_HPP

#include "../Component.hpp"

namespace ses
{

class PhysicComponent : public Component
{
    public:
        PhysicComponent();
        PhysicComponent(float mass);
        virtual ~PhysicComponent();

        void setMass(float mass);
        float getMass() const;

    protected:
        float mMass;
};

} // namespace ses

#endif // SES_PHYSICCOMPONENT_HPP
