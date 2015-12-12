#include "GameState.hpp"
#include "../Map/Test/BgLayer.hpp"
#include "../Map/Test/TileLayer.hpp"
#include <iostream>

GameState::GameState(ah::StateManager& manager)
: ah::State(manager,lp::type<GameState>())
, mWorld("Assets/Data/game.xml")
{
    ses::RenderSystem& rs = mWorld.addSystem<ses::RenderSystem>();
    ses::PhysicSystem& ps = mWorld.addSystem<ses::PhysicSystem>();
    ses::AudioSystem& as = mWorld.addSystem<ses::AudioSystem>();
    PlayerInputSystem& is = mWorld.addSystem<PlayerInputSystem>();

    if (!mWorld.load("Assets/Data/game.xml"))
    {
        std::cout << "Generating a new game" << std::endl;
        {
            auto e = mWorld.instantiate("player");
            e->setPosition(400.f,100.f);
            e->setOrigin(64.f,64.f);
            e->addComponent<ses::SpriteComponent>("icon");
            e->addComponent<ses::AudioListenerComponent>();
            e->addComponent<ses::CameraComponent>();

            b2BodyDef bDef;
            bDef.type = b2_dynamicBody;
            bDef.position.Set(ses::Physic::pixelsToMeters(400.f),ses::Physic::pixelsToMeters(100.f));
            bDef.angle = 0;
            b2PolygonShape bShape;
            bShape.SetAsBox(2,2);
            b2FixtureDef fDef;
            fDef.shape = &bShape;
            fDef.density = 5;
            ses::PhysicComponent& pc = e->addComponent<ses::PhysicComponent>();
            pc.init(&ps.getWorld(),&bDef,&fDef);
        }

        {
            auto e = mWorld.instantiate("wall");
            e->setPosition(900.f,100.f);
            e->setOrigin(64.f,64.f);
            e->addComponent<ses::SpriteComponent>("icon");

            b2BodyDef bDef;
            bDef.type = b2_staticBody;
            bDef.position.Set(ses::Physic::pixelsToMeters(900.f),ses::Physic::pixelsToMeters(100.f));
            bDef.angle = 0;
            b2PolygonShape bShape;
            bShape.SetAsBox(2,2);
            b2FixtureDef fDef;
            fDef.shape = &bShape;
            fDef.density = 5;
            ses::PhysicComponent& pc = e->addComponent<ses::PhysicComponent>();
            pc.init(&ps.getWorld(),&bDef,&fDef);
        }

        {
            auto l = mWorld.instantiate("layer");
            l->setPositionZ(-100.f);
            l->addComponent<ses::LayerComponent>().setLayer<BgLayer>();
        }

        {
            auto l = mWorld.instantiate("tiles");
            l->setPositionZ(-50.f);
            l->addComponent<ses::LayerComponent>().setLayer<TileLayer>();
        }

    }
}

GameState::~GameState()
{
}

bool GameState::handleEvent(sf::Event const& event)
{
    mWorld.getSystem<PlayerInputSystem>().handleEvent(event);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        requestClear();
        requestPush(lp::type<MenuState>());
    }
    return true;
}

bool GameState::update(sf::Time dt)
{
    mWorld.getSystem<ses::PhysicSystem>().update(dt);
    mWorld.getSystem<PlayerInputSystem>().update();

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
