#ifndef SES_CAMERACOMPONENT_HPP
#define SES_CAMERACOMPONENT_HPP

#include <SFML/Graphics/View.hpp>

#include "../Component.hpp"

namespace ses
{

class CameraComponent : public Component
{
    public:
        CameraComponent();
        CameraComponent(sf::View const& view);
        virtual ~CameraComponent();

        void setView(sf::View const& view);
        sf::View& getView();

        void update();

        sf::FloatRect getViewRect() const;

        void load(pugi::xml_node& node);
        void save(pugi::xml_node& node);

    protected:
        sf::View mView;
};

} // namespace ses

#endif // SES_CAMERACOMPONENT_HPP
