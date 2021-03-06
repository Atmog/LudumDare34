#ifndef SES_PHYSICSYSTEM_HPP
#define SES_PHYSICSYSTEM_HPP

#include <SFML/System/Time.hpp>

#include <Box2D/Box2D.h>

#include "../System.hpp"

namespace ses
{

namespace Physic
{
    constexpr double PIXELS_PER_METERS = 32.0;
    constexpr double PI = 3.14159265358979323846;

    template<typename T>
    constexpr T pixelsToMeters(const T& x)
    {
        return x/PIXELS_PER_METERS;
    }

    template<typename T>
    constexpr T metersToPixels(const T& x)
    {
        return x*PIXELS_PER_METERS;
    }

    template<typename T>
    constexpr T degToRad(const T& x)
    {
        return PI*x/180.0;
    }

    template<typename T>
    constexpr T radToDeg(const T& x)
    {
        return 180.0*x/PI;
    }
} // namespace PhysicConverter

class PhysicSystem : public System
{
    public:
        PhysicSystem();
        virtual ~PhysicSystem();

        void setGravity(sf::Vector2f const& gravity);
        sf::Vector2f getGravity() const;

        b2World& getWorld();

        void update(sf::Time dt);

    protected:
        ComponentFilter mFilter;

        b2World* mPhysicWorld;
};

} // namespace ses

#endif // SES_PHYSICSYSTEM_HPP
