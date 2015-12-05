#ifndef SES_SYSTEM_HPP
#define SES_SYSTEM_HPP

#include <memory>
#include <vector>

#include "ComponentFilter.hpp"
#include "Packet.hpp"
#include "Utility.hpp"
#include "Entity.hpp"

namespace ses
{

class World;

class System
{
    public:
        System();
        virtual ~System();

        typedef std::unique_ptr<System> Ptr;

        virtual void handleMessage(sf::Packet& packet);

        friend World;

    protected:
        World* mWorld;
};

} // namespace ses

#endif // SES_SYSTEM_HPP
