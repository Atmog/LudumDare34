#include "Game.hpp"

Game Game::mInstance;

std::string Game::getTitle()
{
    return "Test";
}

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}
