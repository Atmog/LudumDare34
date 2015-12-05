#include "Tile.hpp"
#include "../../Application/Application.hpp"

Tile::Tile()
{
    mSprite.setTexture(ah::Application::getResources().getTexture("icon"));
}
