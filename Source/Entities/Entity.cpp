#include "Entity.hpp"
#include "Components.hpp"
#include "World.hpp"

namespace ses
{

Entity::Entity(const Id& id) : mId(id), mZ(0.f), mNeedRemove(false)
{
}

Entity::~Entity()
{
    removeComponents();
    mNeedRemove = true;
}

const Id& Entity::getId() const
{
    return mId;
}

void Entity::setPositionZ(float z)
{
    mZ = z;
}

float Entity::getPositionZ() const
{
    return mZ;
}

bool Entity::hasComponent(std::string const& componentId)
{
    auto itr = mComponents.find(componentId);
    if (itr != mComponents.end())
    {
        return true;
    }
    return false;
}

bool Entity::hasComponents(ComponentFilter const& filter)
{
    return filter.passFilter(this);
}

void Entity::removeComponents()
{
    mComponents.clear();
}

void Entity::remove()
{
    removeComponents();
    mNeedRemove = true;
}

bool Entity::needRemove() const
{
    return mNeedRemove;
}

void Entity::load(pugi::xml_node& node)
{
    pugi::xml_node data = node.child("Data");
    setPosition(data.attribute("pos-x").as_float(),data.attribute("pos-y").as_float());
    setPositionZ(data.attribute("pos-z").as_float());
    setOrigin(data.attribute("ori-x").as_float(),data.attribute("ori-y").as_float());
    setScale(data.attribute("sca-x").as_float(),data.attribute("sca-y").as_float());
    setRotation(data.attribute("rot").as_float());

    pugi::xml_node components = node.child("Components");
    if (components)
    {
        for (pugi::xml_node component = components.child("Component"); component; component = component.next_sibling("Component"))
        {
            std::string id = component.attribute("id").value();
            // TODO : load components depending on their types
            if (id == "ses::AudioListenerComponent")
            {
                addComponent<ses::AudioListenerComponent>().load(component);
            }
            if (id == "ses::AudioSourceComponent")
            {
                addComponent<ses::AudioSourceComponent>().load(component);
            }
            if (id == "ses::CameraComponent")
            {
                addComponent<ses::CameraComponent>().load(component);
            }
            if (id == "ses::PhysicComponent")
            {
                addComponent<ses::PhysicComponent>().load(component);
            }
            if (id == "ses::SpriteComponent")
            {
                addComponent<ses::SpriteComponent>().load(component);
            }
            if (id == "ses::LayerComponent")
            {
                addComponent<ses::LayerComponent>().load(component);
            }
        }
    }
}

void Entity::save(pugi::xml_node& node)
{
    if (!needRemove() && true) // TODO : detect if storable entity
    {
        pugi::xml_node entity = node.append_child("Entity");
        entity.append_attribute("id") = mId.getKey().c_str();

        pugi::xml_node data = entity.append_child("Data");
        data.append_attribute("pos-x") = getPosition().x;
        data.append_attribute("pos-y") = getPosition().y;
        data.append_attribute("pos-z") = getPositionZ();
        data.append_attribute("ori-x") = getOrigin().x;
        data.append_attribute("ori-y") = getOrigin().y;
        data.append_attribute("sca-x") = getScale().x;
        data.append_attribute("sca-y") = getScale().y;
        data.append_attribute("rot") = getRotation();

        pugi::xml_node components = entity.append_child("Components");
        for (auto itr = mComponents.begin(); itr != mComponents.end(); itr++)
        {
            pugi::xml_node component = components.append_child("Component");
            component.append_attribute("id") = itr->first.c_str();
            itr->second->save(component);
        }
    }
}

void Entity::setWorld(World* world)
{
    mWorld = world;
}

World* Entity::getWorld()
{
    return mWorld;
}

} // namespace ses
