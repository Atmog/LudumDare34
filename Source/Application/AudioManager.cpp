#include "AudioManager.hpp"
#include "Application.hpp"

namespace ah
{

AudioManager::AudioManager()
{
    mStatus = sf::SoundSource::Playing;
    if (!load())
    {
        mGlobalVolume = 100.f;
        mMusicVolume = 100.f;
        mSoundVolume = 100.f;
        save();
    }
}

AudioManager::~AudioManager()
{
    save();
}

void AudioManager::registerMusicFile(std::string const& id, std::string const& filename)
{
    mMusicFilenames[id] = filename;
}

std::size_t AudioManager::playMusic(std::string const& id, bool loop, sf::Vector2f const& position)
{
    std::string filename;
    if (mMusicFilenames.find(id) != mMusicFilenames.end())
    {
        filename = mMusicFilenames.at(id);
    }
    else
    {
        filename = id;
    }

    auto m = std::make_shared<Music>(filename,loop,position);
    if (m != nullptr && mStatus != sf::SoundSource::Stopped)
    {
        mAudioSources[m->getId()] = m;
        m->setVolume(mMusicVolume);
        m->play();
        if (mStatus == sf::SoundSource::Paused)
        {
            m->pause();
        }
        return m->getId();
    }
    return 0;
}

std::size_t AudioManager::playSound(std::string const& id, bool loop, sf::Vector2f const& position)
{
    if (ah::Application::getResources().isLoadedSoundBuffer(id))
    {
        auto s = std::make_shared<Sound>(ah::Application::getResources().getSoundBuffer(id),loop,position);
        if (s != nullptr && mStatus != sf::SoundSource::Stopped)
        {
            mAudioSources[s->getId()] = s;
            s->setVolume(mSoundVolume);
            s->play();
            if (mStatus == sf::SoundSource::Paused)
            {
                s->pause();
            }
            return s->getId();
        }
    }
    return 0;
}

std::size_t AudioManager::playPlaylist(std::vector<std::string> const& filenames, bool loop, sf::Vector2f const& position)
{
    auto p = std::make_shared<Playlist>(filenames,loop,position);
    if (p != nullptr && mStatus != sf::SoundSource::Stopped)
    {
        mAudioSources[p->getId()] = p;
        p->setVolume(mMusicVolume);
        p->play();
        if (mStatus == sf::SoundSource::Paused)
        {
            p->pause();
        }
        return p->getId();
    }
    return 0;
}

std::shared_ptr<AudioSource> AudioManager::getAudioSource(std::size_t const& id)
{
    if (mAudioSources.find(id) != mAudioSources.end())
    {
        return mAudioSources.at(id);
    }
    return nullptr;
}

void AudioManager::play()
{
    if (mStatus == sf::SoundSource::Paused) // If stopped there is no audios
    {
        update(); // Remove Stopped Audios
        for (auto itr = mAudioSources.begin(); itr != mAudioSources.end(); itr++)
        {
            itr->second->play(); // All audios are paused so play them
        }
        mStatus = sf::SoundSource::Playing;
    }
}

void AudioManager::pause()
{
    if (mStatus == sf::SoundSource::Playing)
    {
        update(); // Remove Stopped Audios
        for (auto itr = mAudioSources.begin(); itr != mAudioSources.end(); itr++)
        {
            itr->second->pause(); // All audios are playing so pause them
        }
        mStatus = sf::SoundSource::Paused;
    }
}

void AudioManager::stop()
{
    if (mStatus != sf::SoundSource::Stopped)
    {
        mAudioSources.clear(); // Remove all
    }
}

void AudioManager::update()
{
    for (auto itr = mAudioSources.begin(); itr != mAudioSources.end(); itr++)
    {
        itr->second->update();
        if (mStatus != sf::SoundSource::Stopped && itr->second->getStatus() == sf::SoundSource::Stopped)
        {
            mAudioSources.erase(itr); // Remove stopped audios
        }
    }
}

void AudioManager::setGlobalVolume(float volume)
{
    mGlobalVolume = volume;
    sf::Listener::setGlobalVolume(volume);
}

void AudioManager::setMusicVolume(float volume)
{
    mMusicVolume = volume;
    for (auto itr = mAudioSources.begin(); itr != mAudioSources.end(); itr++)
    {
        if (itr->second->getType() == AudioSource::Type::Music)
        {
            itr->second->setVolume(volume);
        }
    }
}

void AudioManager::setSoundVolume(float volume)
{
    mSoundVolume = volume;
    for (auto itr = mAudioSources.begin(); itr != mAudioSources.end(); itr++)
    {
        if (itr->second->getType() == AudioSource::Type::Sound)
        {
            itr->second->setVolume(volume);
        }
    }
}

float AudioManager::getGlobalVolume() const
{
    return mGlobalVolume;
}

float AudioManager::getMusicVolume() const
{
    return mMusicVolume;
}

float AudioManager::getSoundVolume() const
{
    return mSoundVolume;
}

bool AudioManager::load()
{
    pugi::xml_document doc;
    if (!doc.load_file("Assets/Data/settings.xml"))
    {
        return false;
    }
    pugi::xml_node audio = doc.child("Audio");
    if (audio)
    {
        mGlobalVolume = audio.child("Global").attribute("value").as_float();
        mMusicVolume = audio.child("Music").attribute("value").as_float();
        mSoundVolume = audio.child("Sound").attribute("value").as_float();
        return true;
    }
    return false;
}

void AudioManager::save()
{
    pugi::xml_document doc;
    doc.load_file("Assets/Data/settings.xml");
    if (doc.child("Audio"))
    {
        doc.remove_child("Audio");
    }
    pugi::xml_node audio = doc.append_child("Audio");
    audio.append_child("Global").append_attribute("value") = mGlobalVolume;
    audio.append_child("Music").append_attribute("value") = mMusicVolume;
    audio.append_child("Sound").append_attribute("value") = mSoundVolume;
    doc.save_file("Assets/Data/settings.xml");
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

std::size_t AudioSource::mIdCounter = 0;

AudioSource::AudioSource() : mId(++mIdCounter)
{
}

AudioSource::~AudioSource()
{
}

void AudioSource::play()
{
}

void AudioSource::pause()
{
}

void AudioSource::stop()
{
}

void AudioSource::update()
{
}

sf::SoundSource::Status AudioSource::getStatus()
{
    return sf::SoundSource::Stopped;
}

void AudioSource::setVolume(float volume)
{
}

void AudioSource::setPosition(sf::Vector2f const& position)
{
}

void AudioSource::setLoop(bool loop)
{
}

float AudioSource::getVolume()
{
    return 100.f;
}

sf::Vector2f AudioSource::getPosition()
{
    return sf::Vector2f();
}

bool AudioSource::getLoop()
{
    return false;
}

std::size_t AudioSource::getId() const
{
    return mId;
}

AudioSource::Type AudioSource::getType() const
{
    return mType;
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

Music::Music(std::string const& filename, bool loop, sf::Vector2f const& position)
{
    mType = AudioSource::Type::Music;

    mMusic.openFromFile(filename);
    mMusic.setLoop(loop);
    mMusic.setPosition(position.x,0.f,position.y);
}

void Music::play()
{
    mMusic.play();
}

void Music::pause()
{
    mMusic.pause();
}

void Music::stop()
{
    mMusic.stop();
}

sf::SoundSource::Status Music::getStatus()
{
    return mMusic.getStatus();
}

void Music::setVolume(float volume)
{
    mMusic.setVolume(volume);
}

void Music::setPosition(sf::Vector2f const& position)
{
    mMusic.setPosition(position.x,0.f,position.y);
}

void Music::setLoop(bool loop)
{
    mMusic.setLoop(loop);
}

float Music::getVolume()
{
    return mMusic.getVolume();
}

sf::Vector2f Music::getPosition()
{
    return sf::Vector2f(mMusic.getPosition().x,mMusic.getPosition().z);
}

bool Music::getLoop()
{
    return mMusic.getLoop();
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

Sound::Sound(sf::SoundBuffer& soundBuffer, bool loop, sf::Vector2f const& position)
{
    mType = AudioSource::Type::Sound;

    mSound.setBuffer(soundBuffer);
    mSound.setLoop(loop);
    mSound.setPosition(position.x,0.f,position.y);
}

void Sound::play()
{
    mSound.play();
}

void Sound::pause()
{
    mSound.pause();
}

void Sound::stop()
{
    mSound.stop();
}

sf::SoundSource::Status Sound::getStatus()
{
    return mSound.getStatus();
}

void Sound::setVolume(float volume)
{
    mSound.setVolume(volume);
}

void Sound::setPosition(sf::Vector2f const& position)
{
    mSound.setPosition(position.x,0.f,position.y);
}

void Sound::setLoop(bool loop)
{
    mSound.setLoop(loop);
}

float Sound::getVolume()
{
    return mSound.getVolume();
}

sf::Vector2f Sound::getPosition()
{
    return sf::Vector2f(mSound.getPosition().x,mSound.getPosition().z);
}

bool Sound::getLoop()
{
    return mSound.getLoop();
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

Playlist::Playlist(std::vector<std::string> const& filenames, bool loop, sf::Vector2f const& position)
{
    mType = AudioSource::Type::Music;
    mActualId = 0;
    mFilenames = filenames;
    mLoop = loop;

    if (mFilenames.size() > 0)
    {
        mMusic.openFromFile(mFilenames[mActualId]);
    }
    mMusic.setPosition(position.x,0.f,position.y);
    mStatus = mMusic.getStatus();
}

void Playlist::play()
{
    mMusic.play();
    mStatus = sf::SoundSource::Playing;
}

void Playlist::pause()
{
    mMusic.pause();
    mStatus = sf::SoundSource::Paused;
}

void Playlist::stop()
{
    mMusic.stop();
    mStatus = sf::SoundSource::Stopped;
}

void Playlist::update()
{
    if (mMusic.getStatus() != mStatus)
    {
        if ((mActualId == mFilenames.size()-1 && mLoop) || mActualId < mFilenames.size()-1)
        {
            mActualId = (mActualId + 1) % (mFilenames.size());
            mMusic.openFromFile(mFilenames[mActualId]);
            mMusic.play();
        }
        else
        {
            mStatus = sf::SoundSource::Stopped;
            //mStatus = mMusic.getStatus(); // Is it better ?
        }
    }
}

sf::SoundSource::Status Playlist::getStatus()
{
    return mStatus;
}

void Playlist::setVolume(float volume)
{
    mMusic.setVolume(volume);
}

void Playlist::setPosition(sf::Vector2f const& position)
{
    mMusic.setPosition(position.x,0.f,position.y);
}

void Playlist::setLoop(bool loop)
{
    mMusic.setLoop(loop);
}

float Playlist::getVolume()
{
    return mMusic.getVolume();
}

sf::Vector2f Playlist::getPosition()
{
    return sf::Vector2f(mMusic.getPosition().x,mMusic.getPosition().z);
}

bool Playlist::getLoop()
{
    return mMusic.getLoop();
}

} // namespace ah
