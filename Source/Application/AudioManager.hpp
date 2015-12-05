#ifndef AH_AUDIOMANAGER_HPP
#define AH_AUDIOMANAGER_HPP

#include <map>
#include <memory>

#include <SFML/Audio.hpp>

namespace ah
{

class AudioSource;
class AudioManager
{
    public:
        AudioManager();
        ~AudioManager();

        void registerMusicFile(std::string const& id, std::string const& filename);

        std::size_t playMusic(std::string const& id, bool loop = false, sf::Vector2f const& position = sf::Vector2f());
        std::size_t playSound(std::string const& id, bool loop = false, sf::Vector2f const& position = sf::Vector2f());
        std::size_t playPlaylist(std::vector<std::string> const& filenames, bool loop = false, sf::Vector2f const& position = sf::Vector2f());

        std::shared_ptr<AudioSource> getAudioSource(std::size_t const& id);

        void play();
        void pause();
        void stop();

        void update();

        void setGlobalVolume(float volume);
        void setMusicVolume(float volume);
        void setSoundVolume(float volume);
        float getGlobalVolume() const;
        float getMusicVolume() const;
        float getSoundVolume() const;

        bool load();
        void save();

    protected:
        std::map<std::string,std::string> mMusicFilenames;
        std::map<std::size_t,std::shared_ptr<AudioSource>> mAudioSources;
        sf::SoundSource::Status mStatus;

        float mGlobalVolume;
        float mMusicVolume;
        float mSoundVolume;
};

class AudioSource
{
    public:
        AudioSource();
        virtual ~AudioSource();

        typedef std::shared_ptr<AudioSource> Ptr;

        virtual void play();
        virtual void pause();
        virtual void stop();
        virtual void update();
        virtual sf::SoundSource::Status getStatus();

        enum Type
        {
            Music,
            Sound,
        };

        virtual void setVolume(float volume);
        virtual void setPosition(sf::Vector2f const& position);
        virtual void setLoop(bool loop);
        virtual float getVolume();
        virtual sf::Vector2f getPosition();
        virtual bool getLoop();

        std::size_t getId() const;
        Type getType() const;

    protected:
        std::size_t mId;
        Type mType;

        static std::size_t mIdCounter;
};

class Music : public AudioSource
{
    public:
        Music(std::string const& filename, bool loop, sf::Vector2f const& position);

        void play();
        void pause();
        void stop();
        sf::SoundSource::Status getStatus();

        void setVolume(float volume);
        void setPosition(sf::Vector2f const& position);
        void setLoop(bool loop);
        float getVolume();
        sf::Vector2f getPosition();
        bool getLoop();

    private:
        sf::Music mMusic;
};

class Sound : public AudioSource
{
    public:
        Sound(sf::SoundBuffer& soundBuffer, bool loop, sf::Vector2f const& position);

        void play();
        void pause();
        void stop();
        sf::SoundSource::Status getStatus();

        void setVolume(float volume);
        void setPosition(sf::Vector2f const& position);
        void setLoop(bool loop);
        float getVolume();
        sf::Vector2f getPosition();
        bool getLoop();

    private:
        sf::Sound mSound;
};

class Playlist : public AudioSource
{
    public:
        Playlist(std::vector<std::string> const& filenames, bool loop, sf::Vector2f const& position);

        void play();
        void pause();
        void stop();
        void update();
        sf::SoundSource::Status getStatus();

        void setVolume(float volume);
        void setPosition(sf::Vector2f const& position);
        void setLoop(bool loop);
        float getVolume();
        sf::Vector2f getPosition();
        bool getLoop();

    protected:
        sf::Music mMusic;
        sf::SoundSource::Status mStatus;
        std::size_t mActualId;
        std::vector<std::string> mFilenames;
        bool mLoop;
};

} // namespace ah

#endif // AH_AUDIOMANAGER_HPP
