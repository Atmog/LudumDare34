#ifndef SES_AUDIOSYSTEM_HPP
#define SES_AUDIOSYSTEM_HPP

#include <algorithm>
#include <map>
#include <vector>

#include <SFML/Audio.hpp>

#include "../System.hpp"
#include "../Components.hpp"

namespace ses
{

class AudioSystem : public System
{
    public:
        AudioSystem();
        virtual ~AudioSystem();

        bool loadSound(std::string const& filename, std::string const& id = "");
        //bool loadMusic(std::string const& filename, std::string const& id = "");

        void playSound(std::string const& id, Id const& eId);
        //void playMusic(std::string const& id, Id const& eId, bool loop = true);
        //void stopMusic(std::string const& id, Id const& eId);

        void update();

    protected:
        ComponentFilter mFilter;

        std::map<std::string,sf::SoundBuffer> mSoundBuffers;
        //std::map<std::string,std::string> mMusicIds;

        std::map<std::string,std::vector<sf::Sound>> mSounds;
        //std::map<std::string,std::map<std::string,sf::Music>> mMusics;
};

} // namespace ses

#endif // SES_AUDIOSYSTEM_HPP
