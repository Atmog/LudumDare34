#ifndef SES_LAYERCOMPONENT_HPP
#define SES_LAYERCOMPONENT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "../Component.hpp"

#include "../../Map/Layer.hpp"
#include "../../Helper/TypeToString.hpp"

namespace ses
{

class LayerComponent : public Component, public sf::Drawable
{
    public:
        LayerComponent();
        virtual ~LayerComponent();

        template <typename T>
        void setLayer();
        template <typename T>
        T& getLayer();

        sf::FloatRect getBounds() const;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void load(pugi::xml_node& node);
        void save(pugi::xml_node& node);

    private:
        map::Layer* mLayer;
        std::string mLayerType;
};

template <typename T>
void LayerComponent::setLayer()
{
    mLayer = new T();
    mLayerType = lp::type<T>();
}

template <typename T>
T& LayerComponent::getLayer()
{
    return static_cast<T&>(*mLayer);
}

} // namespace ses

#endif // SES_LAYERCOMPONENT_HPP
