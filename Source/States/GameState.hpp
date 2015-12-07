#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Application/Application.hpp"
#include "../Application/State.hpp"
#include "States.hpp"

#include <SFML/Graphics/Sprite.hpp> // temp test
#include "../Entities/Systems.hpp"
#include "../Entities/Components.hpp"
#include "../Entities/World.hpp"

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
        ses::World mWorld;
};

#endif // GAMESTATE_HPP
