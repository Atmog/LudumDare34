#include "GameState.hpp"

GameState::GameState(ah::StateManager& manager)
: ah::State(manager,lp::type<GameState>())
{
    ses::RenderSystem& rs = mWorld.addSystem<ses::RenderSystem>();
    ses::PhysicSystem& ps = mWorld.addSystem<ses::PhysicSystem>();
    ses::AudioSystem& as = mWorld.addSystem<ses::AudioSystem>();

    auto e = mWorld.instantiate("player");
    e->setPosition(400.f,100.f);
    e->setOrigin(64.f,64.f);
    e->addComponent<ses::SpriteComponent>(ah::Application::getResources().getTexture("icon"));
    e->addComponent<ses::AudioListenerComponent>();

    b2BodyDef bDef;
    bDef.type = b2_dynamicBody;
    bDef.position.Set(ses::Physic::pixelsToMeters(400.f),ses::Physic::pixelsToMeters(100.f));
    bDef.angle = 0;
    b2PolygonShape bShape;
    bShape.SetAsBox(2,2);
    b2FixtureDef fDef;
    fDef.shape = &bShape;
    fDef.density = 5;
    e->addComponent<ses::PhysicComponent>(ps.getWorld(),bDef,fDef);

}

GameState::~GameState()
{
}

bool GameState::handleEvent(sf::Event const& event)
{
    return true;
}

bool GameState::update(sf::Time dt)
{
    mWorld.getSystem<ses::PhysicSystem>().update(dt);

    ses::Entity::Ptr player = mWorld.getEntity("player");
    if (player != nullptr)
    {
        b2Body* body = player->getComponent<ses::PhysicComponent>().getBody();
        if (body != nullptr)
        {
            b2Vec2 vel = body->GetLinearVelocity();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                vel.x = -5;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                vel.x = 5;
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                vel.x = 0;
                sf::Vector2f pos = ah::Application::getWindow().getMousePosition();
                b2Vec2 p;
                p.x = ses::Physic::pixelsToMeters(pos.x);
                p.y = ses::Physic::pixelsToMeters(pos.y);
                body->SetTransform(p,body->GetAngle());
            }
            else
            {
                vel.x = 0;
            }
            body->SetLinearVelocity( vel );
        }
    }

    mWorld.update();
    return true;
}

void GameState::render(sf::RenderTarget& target, sf::RenderStates states)
{
    states.transform *= getTransform();
    mWorld.getSystem<ses::RenderSystem>().render(target);
}

void GameState::onActivate()
{
}

void GameState::onDeactivate()
{
}
