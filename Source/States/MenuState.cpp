#include "MenuState.hpp"

MenuState::MenuState(ah::StateManager& manager)
: ah::State(manager,lp::type<MenuState>())
{
    sf::Vector2u wSize = ah::Application::getWindow().getSize();
    sf::Vector2f scale = sf::Vector2f(wSize.x/800.f,wSize.y/600.f);

    auto buttonGame = sfg::Button::Create("Play");
	buttonGame->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        ah::Application::getAudio().playSound("jingle");
    });
	buttonGame->SetAllocation(sf::FloatRect(wSize.x / 2 - 200, 200.f, 400, 75));
	buttonGame->SetClass("menu_button");

	auto buttonSettings = sfg::Button::Create("Settings");
	buttonSettings->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        ah::Application::getAudio().playSound("jingle");
    });
	buttonSettings->SetAllocation(sf::FloatRect(wSize.x / 2 - 200, 325.f, 400, 75));
	buttonSettings->SetClass("menu_button");

	auto buttonQuit = sfg::Button::Create("Quit");
	buttonQuit->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        ah::Application::getWindow().close();
    });
	buttonQuit->SetAllocation(sf::FloatRect(wSize.x / 2 - 200, 450.f, 400, 75));
	buttonQuit->SetClass("menu_button");

	sfg::Context::Get().GetEngine().SetProperties(
		"Button.menu-button"
		"{"
		"	FontSize: " + std::to_string(static_cast<unsigned int>(25 * scale.y)) + ";"
		"}"
	);

	mDesktop.Add(buttonGame);
	mDesktop.Add(buttonSettings);
	mDesktop.Add(buttonQuit);
	mDesktop.LoadThemeFromFile("Assets/Data/theme.css");

	mBackground.setScale(scale);
	mBackground.setTexture(ah::Application::getResources().getTexture("bg"));

	mTitleText.setFont(ah::Application::getResources().getFont("atmog"));
    mTitleText.setString(Game::getTitle());
    mTitleText.setCharacterSize(static_cast<unsigned int>(80 * scale.y));
    mTitleText.setPosition(wSize.x * 0.5f - mTitleText.getGlobalBounds().width * 0.5f, 25.f);
    mTitleText.setColor(sf::Color::White);

    mTitleShadow.setFont(ah::Application::getResources().getFont("atmog"));
    mTitleShadow.setString(mTitleText.getString());
    mTitleShadow.setCharacterSize(mTitleText.getCharacterSize());
    mTitleShadow.setPosition(mTitleText.getPosition() + sf::Vector2f(2.f * scale.x, 2.f * scale.y));
    mTitleShadow.setColor(sf::Color::Black);
}

MenuState::~MenuState()
{
}

bool MenuState::handleEvent(sf::Event const& event)
{
    mDesktop.HandleEvent(event);
    return true;
}

bool MenuState::update(sf::Time dt)
{
    mDesktop.Update(dt.asSeconds());
    return true;
}

void MenuState::render(sf::RenderTarget& target, sf::RenderStates states)
{
    states.transform *= getTransform();
    target.draw(mBackground,states);
    mSfgui.Display(ah::Application::getWindow());
    target.draw(mTitleShadow,states);
    target.draw(mTitleText,states);
}

void MenuState::onActivate()
{
    ah::Application::getWindow().useCustomMouseCursor(&ah::Application::getResources().getTexture("cursor"));
}

void MenuState::onDeactivate()
{
}
