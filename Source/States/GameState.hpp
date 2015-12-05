#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Application/Application.hpp"
#include "../Application/State.hpp"
#include "States.hpp"

#include <SFML/Graphics/Sprite.hpp> // temp test
#include "../Map/Map.hpp" // temp test
#include "../Map/Test/TileLayer.hpp" // temp tests

class GameState : public ah::State
{
    public:
        GameState(ah::StateManager& manager);
        virtual ~GameState();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render(sf::RenderTarget& target, sf::RenderStates states);

        void onActivate();
        void onDeactivate();

    protected:
        sf::Sprite mSprite;
        map::Map mMap;
};

#endif // GAMESTATE_HPP
