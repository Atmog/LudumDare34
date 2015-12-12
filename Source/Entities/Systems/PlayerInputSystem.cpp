#include "PlayerInputSystem.hpp"
#include "../World.hpp"
#include <Box2D/Box2D.h>
#include <iostream>

PlayerInputSystem::PlayerInputSystem() : ses::System(), lp::ActionTarget(Game::getActionMap())
{
}

PlayerInputSystem::~PlayerInputSystem()
{
}

void PlayerInputSystem::update()
{
    mMap->invokeCallbacks(mSystem,&(ah::Application::getWindow()));

    auto player = mWorld->getEntity("player");
    b2Body* body = player->getComponent<ses::PhysicComponent>().getBody();
    b2Vec2 vel = body->GetLinearVelocity();

    if (isActive("right"))
    {
        vel.x = 5;
    }
    else if (isActive("left"))
    {
        vel.x = -5;
    }
    else
    {
        vel.x = 0;
    }
    body->SetLinearVelocity( vel );

    mMap->clearEvents();
}
