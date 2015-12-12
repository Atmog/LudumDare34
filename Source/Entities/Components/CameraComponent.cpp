#include "CameraComponent.hpp"
#include "../Entity.hpp"
#include "../../Application/Application.hpp"

namespace ses
{

CameraComponent::CameraComponent() : Component()
{
    mView = ah::Application::getWindow().getDefaultView();
}

CameraComponent::CameraComponent(sf::View const& view) : Component(), mView(view)
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::setView(sf::View const& view)
{
    mView = view;
    update();
}

sf::View& CameraComponent::getView()
{
    update();
    return mView;
}

void CameraComponent::update()
{
    if (mEntity != nullptr)
    {
        mView.setCenter(mEntity->getPosition());
    }
}

sf::FloatRect CameraComponent::getViewRect() const
{
    return sf::FloatRect(mView.getCenter() - mView.getSize() * 0.5f,mView.getSize());
}

void CameraComponent::load(pugi::xml_node& node)
{
    sf::Vector2f center, size;
    center.x = node.attribute("cen-x").as_float();
    center.y = node.attribute("cen-y").as_float();
    size.x = node.attribute("size-x").as_float();
    size.y = node.attribute("size-y").as_float();
    mView.setCenter(center);
    mView.setSize(size);
}

void CameraComponent::save(pugi::xml_node& node)
{
    node.append_attribute("cen-x") = mView.getCenter().x;
    node.append_attribute("cen-y") = mView.getCenter().y;
    node.append_attribute("size-x") = mView.getSize().x;
    node.append_attribute("size-y") = mView.getSize().y;
}

} // namespace ses
