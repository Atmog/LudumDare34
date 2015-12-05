#include "Application/Application.hpp"
#include "States/States.hpp"
#include "Helper/easylogging++.hpp"

INITIALIZE_EASYLOGGINGPP

int main()
{
    ah::Application::getResources().loadImage("icon","Assets/Textures/icon.png");

    ah::Application::getResources().loadTexture("icon","Assets/Textures/icon.png");
    ah::Application::getResources().loadTexture("bg","Assets/Textures/back.png");
    ah::Application::getResources().loadTexture("cursor","Assets/Textures/cursor.png");
    ah::Application::getResources().loadTexture("libs","Assets/Textures/libs.png");
    ah::Application::getResources().loadTexture("ld","Assets/Textures/ld.png");

    ah::Application::getResources().getTexture("ld").setSmooth(true);
    ah::Application::getResources().getTexture("libs").setSmooth(true);
    ah::Application::getResources().getTexture("bg").setSmooth(true);

    ah::Application::getResources().loadFont("cool","Assets/Fonts/coolveticca.ttf");
    ah::Application::getResources().loadFont("atmog","Assets/Fonts/atmogFont.ttf");

    ah::Application::getResources().loadSoundBuffer("jingle","Assets/Sounds/jingleAtmog.wav");

    ah::Application::getWindow().create("Tehos2");
    ah::Application::getWindow().setIcon(&ah::Application::getResources().getImage("icon"));
    ah::Application::getWindow().setDebugInfoFont(&ah::Application::getResources().getFont("cool"));
    ah::Application::getWindow().showDebugInfo(true);

    ah::Application::getStates().registerState<IntroState>();
    ah::Application::getStates().registerState<MenuState>();
    ah::Application::getStates().registerState<GameState>();

    ah::Application::getStates().pushState<MenuState>();

    ah::Application::run();
    return 0;
}
