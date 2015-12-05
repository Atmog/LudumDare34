#include "System.hpp"
#include "World.hpp"

namespace ses
{

System::System()
: mWorld(nullptr)
{
}

System::~System()
{
    mWorld = nullptr;
}

void System::handleMessage(sf::Packet& packet)
{
}

} // namespace ses
