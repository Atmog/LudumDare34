#ifndef SES_RENDERSYSTEM_HPP
#define SES_RENDERSYSTEM_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "../System.hpp"
#include "../Components.hpp"

namespace ses
{

class RenderSystem : public System
{
    public:
        RenderSystem();
        virtual ~RenderSystem();

        void render(sf::RenderTarget& target);

    protected:
        sf::View updateView(sf::FloatRect& viewRect, sf::View defaultView);
        ses::EntityVector getDrawables();

        template<typename T>
        void handleDrawable(sf::RenderTarget& target, sf::RenderStates states, ses::Entity::Ptr e, sf::FloatRect viewRect);

    protected:
        ComponentFilter mFilterCamera;
        ComponentFilter mFilterDrawables;
};

template<typename T>
void RenderSystem::handleDrawable(sf::RenderTarget& target, sf::RenderStates states, ses::Entity::Ptr e, sf::FloatRect viewRect)
{
    if (e->hasComponent<T>())
    {
        if (e->getComponent<T>().getBounds().intersects(viewRect))
        {
            target.draw(e->getComponent<T>(),states);
        }
    }
}

} // namespace ses

#endif // SES_RENDERSYSTEM_HPP
