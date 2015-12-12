#ifndef PLAYERINPUTSYSTEM_HPP
#define PLAYERINPUTSYSTEM_HPP

#include "../System.hpp"
#include "../../Helper/ActionTarget.hpp"
#include "../../Game.hpp"
#include "../../Application/Application.hpp"
#include "../Components.hpp"

class PlayerInputSystem : public ses::System, public lp::ActionTarget
{
    public:
        PlayerInputSystem();
        virtual ~PlayerInputSystem();

        void update();
};

#endif // PLAYERINPUTSYSTEM_HPP
