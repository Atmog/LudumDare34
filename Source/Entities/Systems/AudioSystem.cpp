#include "AudioSystem.hpp"
#include "../World.hpp"

namespace ses
{

AudioSystem::AudioSystem()
{
    mFilter.requires(type<AudioSourceComponent>());
}

AudioSystem::~AudioSystem()
{
}

bool AudioSystem::loadSound(std::string const& filename, std::string const& id)
{
    std::string fId = (id != "") ? id : filename;
    sf::SoundBuffer buffer;
    bool res = buffer.loadFromFile(filename);
    if (res)
    {
        mSoundBuffers[fId] = buffer;
    }
    return res;
}

/*
bool AudioSystem::loadMusic(std::string const& filename, std::string const& id)
{
    std::string fId = (id != "") ? id : filename;
    sf::Music music;
    bool res = music.openFromFile(filename);
    if (res)
    {
        mMusicIds[fId] = filename;
    }
    return res;
}*/

void AudioSystem::playSound(std::string const& id, Id const& eId)
{
    if (mSoundBuffers.find(id) == mSoundBuffers.end())
        return;

    mSounds[eId.getKey()].emplace_back();
    mSounds[eId.getKey()].back().setBuffer(mSoundBuffers[id]);
    mSounds[eId.getKey()].back().play();
}

/*
void AudioSystem::playMusic(std::string const& id, Id const& eId, bool loop)
{
    if (mMusicIds.find(id) == mMusicIds.end())
        return;

    mMusics[eId.getKey()][id].openFromFile(mMusicIds[id]);
    mMusics[eId.getKey()][id].setLoop(loop);
    mMusics[eId.getKey()][id].play();
}

void AudioSystem::stopMusic(std::string const& id, Id const& eId)
{
    auto itr = mMusics.find(eId.getKey());
    if (itr != mMusics.end())
    {
        auto itr2 = itr->second.find(id);
        if (itr2 != itr->second.end())
        {
            itr2->second.stop();
            itr->second.erase(itr2);
        }
    }
}*/

void AudioSystem::update()
{
    if (!mWorld)
        return;

    auto e = mWorld->getEntities(mFilter);

    // Update position
    for (std::size_t i = 0; i < e.size(); i++)
    {
        std::string id = e[i]->getId().getKey();
        sf::Vector3f pos = sf::Vector3f(e[i]->getPosition().x,0.f,e[i]->getPosition().y);

        auto itr = mSounds.find(id);
        if (itr != mSounds.end())
        {
            for (std::size_t j = 0; j < itr->second.size(); j++)
            {
                itr->second[j].setPosition(pos);
            }
        }

        /*
        auto itr2 = mMusics.find(id);
        if (itr2 != mMusics.end())
        {
            for (auto it = itr2->second.begin(); it != itr2->second.end(); it++)
            {
                it->second.setPosition(pos);
            }
        }
        */
    }

    // Remove useless sound
    for (auto itr = mSounds.begin(); itr != mSounds.end(); itr++)
    {
        for (std::size_t i = 0; i < itr->second.size(); i++)
        {
            if (itr->second[i].getStatus() != sf::Sound::Status::Playing)
            {
                itr->second.erase(i + itr->second.begin());
            }
        }
        if (itr->second.size() == 0)
        {
            mSounds.erase(itr);
        }
    }

    /*
    // Remove useless music
    for (auto itr = mMusics.begin(); itr != mMusics.end(); itr++)
    {
        for (auto it = itr->second.begin(); it != itr->second.end(); it++)
        {
            if (it->second.getStatus() != sf::Sound::Status::Playing)
            {
                itr->second.erase(it);
            }
        }
        if (itr->second.size() == 0)
        {
            mMusics.erase(itr);
        }
    }
    */
}

} // namespace ses
