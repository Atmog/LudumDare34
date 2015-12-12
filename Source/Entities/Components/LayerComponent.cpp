#include "LayerComponent.hpp"
#include "../Entity.hpp"
#include "../../Map/Test/TileLayer.hpp"
#include "../../Map/Test/BgLayer.hpp"

namespace ses
{

LayerComponent::LayerComponent() : Component()
{
    mLayer = nullptr;
}

LayerComponent::~LayerComponent()
{
}

sf::FloatRect LayerComponent::getBounds() const
{
    sf::Vector2f pos(0.f,0.f);
    sf::Vector2f size(0.f,0.f);
    if (mEntity != nullptr)
    {
        pos = mEntity->getPosition() - mEntity->getOrigin();
    }
    if (mLayer != nullptr)
    {
        size = mLayer->getSizePx();
    }
    return sf::FloatRect(pos,size);
}

void LayerComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mLayer != nullptr)
    {
        target.draw(*mLayer);
    }
}

void LayerComponent::load(pugi::xml_node& node)
{
    mLayerType = node.attribute("layer").value();
    if (mLayerType == "BgLayer")
    {
        setLayer<BgLayer>();
    }
    if (mLayerType == "TileLayer")
    {
        setLayer<TileLayer>();
    }
}

void LayerComponent::save(pugi::xml_node& node)
{
    node.append_attribute("layer") = mLayerType.c_str();
}

} // namespace ses
