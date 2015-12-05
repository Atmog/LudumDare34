#include "Window.hpp"

namespace ah
{

Window::Window()
{
    mTitle = "";
    mVerticalSync = false;
    mVisible = false;
    mKeyRepeat = true;
    mFullscreen = false;
    mCursor = MouseCursor::Default;
    mScreenshotPath = "";
    mDebugInfoVisible = false;
    mDebugInfoColor = sf::Color::White;
    mDebugInfoCharsize = 15;

    if (!load())
    {
        detect();
        save();
    }
}

Window::~Window()
{
    save();
}

void Window::setDefaultView()
{
    setView(getDefaultView());
}

void Window::display()
{
    if (mDebugInfoVisible)
    {
        setDefaultView();
        for (auto itr = mDebugInfo.begin(); itr != mDebugInfo.end(); itr++)
        {
            draw(itr->second);
        }
    }

    if (mCursor == MouseCursor::Custom)
    {
        setDefaultView();
        mCursorSprite.setPosition(getMousePosition());
        draw(mCursorSprite);
    }

    sf::RenderWindow::display();
}

void Window::create(std::string const& title, sf::Uint32 style)
{
    if (mFullscreen)
    {
        create(mVideoMode,title,sf::Style::Fullscreen);
    }
    else
    {
        create(mVideoMode,title,style);
    }
}

void Window::create(sf::VideoMode videoMode, std::string const& title, sf::Uint32 style)
{
    mTitle = title;
    mFullscreen = (style & sf::Style::Fullscreen);
    if (mFullscreen && !videoMode.isValid()) // Error : Invalid mode
    {
        videoMode = sf::VideoMode::getFullscreenModes()[0];
    }
    mVideoMode = videoMode;
    sf::RenderWindow::create(videoMode,title,style);
}

void Window::close()
{
    sf::RenderWindow::close();
    mVisible = false;
}

void Window::setTitle(std::string const& title)
{
    sf::RenderWindow::setTitle(title);
    mTitle = title;
}

std::string Window::getTitle() const
{
    return mTitle;
}

void Window::setVerticalSyncEnabled(bool enabled)
{
    sf::RenderWindow::setVerticalSyncEnabled(enabled);
    mVerticalSync = enabled;
}

bool Window::isVerticalSyncEnabled() const
{
    return mVerticalSync;
}

void Window::setVisible(bool visible)
{
    sf::RenderWindow::setVisible(visible);
    mVisible = visible;
}

bool Window::isVisible() const
{
    return mVisible;
}

void Window::setKeyRepeatEnabled(bool enabled)
{
    sf::RenderWindow::setKeyRepeatEnabled(enabled);
    mKeyRepeat = enabled;
}

bool Window::isKeyRepeatEnabled() const
{
    return mKeyRepeat;
}

void Window::setIcon(std::string const& filename)
{
    if (mIcon.loadFromFile(filename))
    {
        sf::RenderWindow::setIcon(mIcon.getSize().x,mIcon.getSize().y,mIcon.getPixelsPtr());
    }
}

void Window::setIcon(sf::Image* image)
{
    if (image != nullptr)
    {
        mIcon = *image;
        sf::RenderWindow::setIcon(mIcon.getSize().x,mIcon.getSize().y,mIcon.getPixelsPtr());
    }
}

void Window::setMousePosition2i(sf::Vector2i const& position)
{
    sf::Mouse::setPosition(position,*this);
}

void Window::setMousePosition(sf::Vector2f const& position)
{
    sf::Mouse::setPosition(static_cast<sf::Vector2i>(position),*this);
}

void Window::setMousePositionMap(sf::Vector2f const& position)
{
    sf::Mouse::setPosition(mapCoordsToPixel(position));
}

void Window::setMousePositionView(sf::Vector2f const& position, sf::View const& view)
{
    sf::Mouse::setPosition(mapCoordsToPixel(position,view));
}

sf::Vector2i Window::getMousePosition2i() const
{
    return sf::Mouse::getPosition(*this);
}

sf::Vector2f Window::getMousePosition() const
{
    return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this));
}

sf::Vector2f Window::getMousePositionMap() const
{
    return mapPixelToCoords(sf::Mouse::getPosition(*this));
}

sf::Vector2f Window::getMousePositionView(sf::View const& view)
{
    return mapPixelToCoords(sf::Mouse::getPosition(*this),view);
}

void Window::setMouseCursor(MouseCursor cursor)
{
    switch (cursor)
    {
        case MouseCursor::None: hideMouseCursor(); break;
        case MouseCursor::Default: useDefaultMouseCursor(); break;
        case MouseCursor::Custom: useCustomMouseCursor(); break;
        default: break;
    }
}

void Window::hideMouseCursor()
{
    sf::RenderWindow::setMouseCursorVisible(false);
    mCursor = MouseCursor::None;
}

void Window::useDefaultMouseCursor()
{
    sf::RenderWindow::setMouseCursorVisible(true);
    mCursor = MouseCursor::Default;
}

void Window::useCustomMouseCursor(sf::Texture* texture, sf::Vector2f const& origin, sf::IntRect const& textureRect)
{
    sf::RenderWindow::setMouseCursorVisible(false);
    mCursor = MouseCursor::Custom;
    if (texture != nullptr)
    {
        setMouseCursorTexture(texture);
        if (textureRect != sf::IntRect())
        {
            setMouseCursorTextureRect(textureRect);
        }
        if (origin != sf::Vector2f())
        {
            setMouseCursorOrigin(origin);
        }
    }
}

Window::MouseCursor Window::getMouseCursor() const
{
    return mCursor;
}

sf::Sprite& Window::getMouseCursorSprite()
{
    return mCursorSprite;
}

void Window::setMouseCursorTexture(std::string const& filename)
{
    if (mCursorTexture.loadFromFile(filename))
    {
        mCursorSprite.setTexture(mCursorTexture);
    }
}

void Window::setMouseCursorTexture(sf::Texture* texture)
{
    if (texture != nullptr)
    {
        mCursorTexture = *texture;
        mCursorSprite.setTexture(mCursorTexture);
    }
}

void Window::setMouseCursorTextureRect(sf::IntRect const& textureRect)
{
    mCursorSprite.setTextureRect(textureRect);
}

void Window::setMouseCursorOrigin(sf::Vector2f const& origin)
{
    mCursorSprite.setOrigin(origin);
}

void Window::screenshot()
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    std::string timeFormat = "%Y-%m-%d_%H-%M-%S";
    strftime(buffer,80,timeFormat.c_str(),timeinfo);

    capture().saveToFile(mScreenshotPath + std::string(buffer) + ".png");
}

void Window::setScreenshotPath(std::string const& screenshotPath)
{
    mScreenshotPath = screenshotPath;
}

std::string Window::getScreenshotPath() const
{
    return mScreenshotPath;
}

void Window::showDebugInfo(bool visible)
{
    mDebugInfoVisible = visible;
}

bool Window::isDebugInfoVisible() const
{
    return mDebugInfoVisible;
}

void Window::setDebugInfo(std::string const& id, std::string const& value)
{
    auto itr = mDebugInfo.find(id);
    mDebugInfo[id].setString(id + " : " + value);
    if (itr == mDebugInfo.end())
    {
        updateDebugInfo();
    }
}

std::string Window::getDebugInfo(std::string const& id) const
{
    if (mDebugInfo.find(id) != mDebugInfo.end())
    {
        return mDebugInfo.at(id).getString();
    }
    return "";
}

void Window::setDebugInfoFont(std::string const& filename)
{
    if (mDebugInfoFont.loadFromFile(filename))
    {
        updateDebugInfo();
    }
}

void Window::setDebugInfoFont(sf::Font* font)
{
    if (font != nullptr)
    {
        mDebugInfoFont = *font;
        updateDebugInfo();
    }
}

void Window::setDebugInfoColor(sf::Color const& color)
{
    mDebugInfoColor = color;
    updateDebugInfo();
}

void Window::setDebugInfoCharsize(std::size_t charsize)
{
    mDebugInfoCharsize = charsize;
    updateDebugInfo();
}

void Window::removeDebugInfo(std::string const& id)
{
    for (auto itr = mDebugInfo.begin(); itr != mDebugInfo.end(); itr++)
    {
        if (itr->first == id)
        {
            mDebugInfo.erase(itr);
            updateDebugInfo();
        }
    }
}

void Window::removeDebugInfos()
{
    mDebugInfo.clear();
    updateDebugInfo();
}

bool Window::load()
{
    pugi::xml_document doc;
    if (!doc.load_file("Assets/Data/settings.xml"))
    {
        return false;
    }
    pugi::xml_node window = doc.child("Window");
    if (window)
    {
        mVerticalSync = window.child("VerticalSync").attribute("value").as_bool();
        mFullscreen = window.child("Fullscreen").attribute("value").as_bool();
        std::string v = window.child("Resolution").attribute("value").value();
        mVideoMode.width = static_cast<unsigned int>(std::stoi(v.substr(0,v.find(","))));
        mVideoMode.height = static_cast<unsigned int>(std::stoi(v.substr(v.find(",")+1)));
        return true;
    }
    return false;
}

void Window::detect()
{
    mVerticalSync = false; // Might be changed
    mFullscreen = false; // Might be changed
    // Choose the "best" resolution
    mVideoMode = sf::VideoMode(800,600); // Need to be changed
}

void Window::save()
{
    pugi::xml_document doc;
    doc.load_file("Assets/Data/settings.xml");
    if (doc.child("Window"))
    {
        doc.remove_child("Window");
    }
    pugi::xml_node window = doc.append_child("Window");
    window.append_child("VerticalSync").append_attribute("value") = mVerticalSync;
    window.append_child("Fullscreen").append_attribute("value") = mFullscreen;
    window.append_child("Resolution").append_attribute("value") = std::string(std::to_string(mVideoMode.width) + "," + std::to_string(mVideoMode.height)).c_str();
    doc.save_file("Assets/Data/settings.xml");
}

void Window::updateDebugInfo()
{
    float pos = 5.f;
    for (auto itr = mDebugInfo.begin(); itr != mDebugInfo.end(); itr++)
    {
        itr->second.setFont(mDebugInfoFont);
        itr->second.setColor(mDebugInfoColor);
        itr->second.setCharacterSize(mDebugInfoCharsize);
        itr->second.setPosition(sf::Vector2f(5.f,pos));
        pos += itr->second.getGlobalBounds().height + 5.f;
    }
}

} // namespace ah
