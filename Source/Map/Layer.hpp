#ifndef MAP_LAYER_HPP
#define MAP_LAYER_HPP

#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace map
{

class Layer : public sf::Drawable, public sf::Transformable
{
    public:
        Layer();

        void setName(std::string const& name);
        std::string getName() const;

        virtual sf::Vector2f getSizePx() const;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        std::string mName;
};

} // namespace map

#endif // MAP_LAYER_HPP
