#include "Component.hpp"

namespace ses
{

Component::Component() : mEntity(nullptr)
{
}

Component::~Component()
{
    mEntity = nullptr;
}

void Component::load(pugi::xml_node& component)
{

}

void Component::save(pugi::xml_node& component)
{

}

} // namespace ses
