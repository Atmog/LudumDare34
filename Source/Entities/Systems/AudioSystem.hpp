#ifndef SES_AUDIOSYSTEM_HPP
#define SES_AUDIOSYSTEM_HPP

#include <algorithm>
#include <map>
#include <vector>

#include <SFML/Audio.hpp>

#include "../System.hpp"
#include "../Components.hpp"

#include "../../Application/Application.hpp"

namespace ses
{

class AudioSystem : public System
{
    public:
        AudioSystem();
        virtual ~AudioSystem();

        void playSound(std::string const& id);
        void playSound(std::string const& id, Id const& eId, bool dynamic = false);

        void update();

        void handleMessage(sf::Packet& packet);

        typedef std::pair<std::size_t,Id> Source;


    protected:
        std::vector<Source> mSources;
};

} // namespace ses

#endif // SES_AUDIOSYSTEM_HPP
