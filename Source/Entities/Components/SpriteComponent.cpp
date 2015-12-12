#include "SpriteComponent.hpp"
#include "../Entity.hpp"
#include "../../Application/Application.hpp"

namespace ses
{

SpriteComponent::SpriteComponent()
: Component()
, sf::Sprite()
{
    mTextureId = "";
}

SpriteComponent::SpriteComponent(std::string const& textureId, sf::IntRect const& textureRect)
: Component()
, sf::Sprite(ah::Application::getResources().getTexture(textureId))
{
    mTextureId = textureId;
    if (textureRect != sf::IntRect(0,0,0,0))
    {
        setTextureRect(textureRect);
    }
}

SpriteComponent::SpriteComponent(sf::Texture const& texture, sf::IntRect const& textureRect)
: Component()
, sf::Sprite(texture)
{
    mTextureId = "";
    if (textureRect != sf::IntRect(0,0,0,0))
    {
        setTextureRect(textureRect);
    }
}

SpriteComponent::~SpriteComponent()
{
}

sf::FloatRect SpriteComponent::getBounds() const
{
    sf::FloatRect b = getGlobalBounds();
    sf::Vector2f p(b.left,b.top);
    if (mEntity != nullptr)
    {
        p = mEntity->getPosition() - mEntity->getOrigin();
    }
    b.left = p.x;
    b.top = p.y;
    return b;
}

void SpriteComponent::load(pugi::xml_node& node)
{
    mTextureId = node.attribute("texture").value();
    if (mTextureId != "")
    {
        setTexture(ah::Application::getResources().getTexture(mTextureId));
    }
    sf::IntRect tRect;
    tRect.left = node.attribute("left").as_float();
    tRect.top = node.attribute("top").as_float();
    tRect.width = node.attribute("width").as_float();
    tRect.height = node.attribute("height").as_float();
    setTextureRect(tRect);
}

void SpriteComponent::save(pugi::xml_node& node)
{
    if (mTextureId != "")
    {
        node.append_attribute("texture") = mTextureId.c_str();
    }
    node.append_attribute("left") = getTextureRect().left;
    node.append_attribute("top") = getTextureRect().top;
    node.append_attribute("width") = getTextureRect().width;
    node.append_attribute("height") = getTextureRect().height;
}

} // namespace ses
