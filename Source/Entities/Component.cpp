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

} // namespace ses
