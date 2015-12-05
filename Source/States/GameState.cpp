#include "GameState.hpp"

GameState::GameState(ah::StateManager& manager)
: ah::State(manager,lp::type<GameState>())
{
    mSprite.setTexture(ah::Application::getResources().getTexture("bg"));
    mSprite.setScale(ah::Application::getWindow().getSize().x/mSprite.getGlobalBounds().width,ah::Application::getWindow().getSize().y/mSprite.getGlobalBounds().height);


    map::Layer* layer = new TileLayer();
    layer->setPosition(100,100);
    mMap.addLayer(layer);
}

GameState::~GameState()
{
}

bool GameState::handleEvent(sf::Event const& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        ah::Application::getAudio().playSound("jingle");
    }
    return true;
}

bool GameState::update(sf::Time dt)
{
    return true;
}

void GameState::render(sf::RenderTarget& target, sf::RenderStates states)
{
    target.draw(mSprite);
    mMap.render(target);
}

void GameState::onActivate()
{
}

void GameState::onDeactivate()
{
}
