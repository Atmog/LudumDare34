#include "CameraComponent.hpp"
#include "../Entity.hpp"

namespace ses
{

CameraComponent::CameraComponent() : Component()
{
}

CameraComponent::CameraComponent(sf::View const& view) : Component(), mView(view)
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

CameraComponent::~CameraComponent()
{
}

} // namespace ses
