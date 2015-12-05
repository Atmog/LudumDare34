#include "RenderSystem.hpp"
#include "../World.hpp"

namespace ses
{

RenderSystem::RenderSystem()
{
    mFilterCamera.requires(type<CameraComponent>());

    std::vector<std::string> drawableTypes;
    drawableTypes.push_back(type<SpriteComponent>());
    drawableTypes.push_back(type<TileLayerComponent>());
    mFilterDrawables.requiresOne(drawableTypes);
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::render(sf::RenderTarget& target)
{
    if (!mWorld)
    {
        return;
    }

    sf::View old = target.getView();

    sf::FloatRect viewRect;
    target.setView(updateView(viewRect,target.getDefaultView()));

    ses::EntityVector e = getDrawables();
    for (std::size_t i = 0; i < e.size(); i++)
    {
        sf::RenderStates states;
        states.transform = e[i]->getTransform();
        handleDrawable<SpriteComponent>(target,states,e[i],viewRect);
        handleDrawable<TileLayerComponent>(target,states,e[i],viewRect);
    }

    target.setView(old);
}

sf::View RenderSystem::updateView(sf::FloatRect& viewRect, sf::View defaultView)
{
    auto c = mWorld->getEntities(mFilterCamera);
    if (c.size() >= 1)
    {
        defaultView = c[0]->getComponent<CameraComponent>().getView();
    }
    viewRect = sf::FloatRect(defaultView.getCenter() - defaultView.getSize() * 0.5f, defaultView.getSize());
    return defaultView;
}

ses::EntityVector RenderSystem::getDrawables()
{
    ses::EntityVector e = mWorld->getEntities(mFilterDrawables);
    std::sort(e.begin(),e.end(),[](ses::Entity::Ptr a, ses::Entity::Ptr b) -> bool
    {
        if (a->getPositionZ() == b->getPositionZ() && a->getPosition().y == b->getPosition().y)
        {
            return (a->getPosition().x < b->getPosition().x);
        }
        else if (a->getPositionZ() == b->getPositionZ())
        {
            return (a->getPosition().y < b->getPosition().y);
        }
        else
        {
            return (a->getPositionZ() < b->getPositionZ());
        }
    });
    return e;
}

} // namespace ses
