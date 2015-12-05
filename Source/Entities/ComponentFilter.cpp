#include "ComponentFilter.hpp"
#include "Entity.hpp"

namespace ses
{

ComponentFilter::ComponentFilter()
{
}

ComponentFilter::~ComponentFilter()
{
    mRequiredComponents.clear();
    mExcludedComponents.clear();
    mRequiredOneComponents.clear();
}

void ComponentFilter::requires(std::string const& componentId)
{
    mRequiredComponents.push_back(componentId);
}

void ComponentFilter::excludes(std::string const& componentId)
{
    mExcludedComponents.push_back(componentId);
}

void ComponentFilter::requiresOne(std::vector<std::string> componentIds)
{
    mRequiredOneComponents.push_back(componentIds);
}

bool ComponentFilter::passFilter(Entity* entity) const
{
    if (entity == nullptr)
    {
        return false;
    }
    for (std::size_t i = 0; i < mRequiredComponents.size(); i++)
    {
        if (!entity->hasComponent(mRequiredComponents.at(i)))
        {
            return false;
        }
    }
    for (std::size_t i = 0; i < mExcludedComponents.size(); i++)
    {
        if (entity->hasComponent(mExcludedComponents.at(i)))
        {
            return false;
        }
    }
    for (std::size_t i = 0; i < mRequiredOneComponents.size(); i++)
    {
        bool found = false;
        for (std::size_t j = 0; j < mRequiredOneComponents.at(i).size(); j++)
        {
            if (entity->hasComponent(mRequiredOneComponents.at(i).at(j)))
            {
                found = true;
            }
        }
        if (!found)
        {
            return false;
        }
    }
    return true;
}

} // namespace ses
