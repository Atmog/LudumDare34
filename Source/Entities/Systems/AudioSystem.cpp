#include "AudioSystem.hpp"
#include "../World.hpp"

namespace ses
{

AudioSystem::AudioSystem()
{
}

AudioSystem::~AudioSystem()
{
}

void AudioSystem::playSound(std::string const& id)
{
    ah::Application::getAudio().playSound(id);
}

void AudioSystem::playSound(std::string const& id, Id const& eId, bool dynamic)
{
    AudioSystem::Source s;
    s.first = ah::Application::getAudio().playSound(id);
    s.second = eId;

    if (dynamic)
    {
        mSources.push_back(s);
    }

    if (mWorld != nullptr)
    {
        auto e = mWorld->getEntity(s.second);
        if (e != nullptr)
        {
            ah::Application::getAudio().getAudioSource(s.first)->setPosition(e->getPosition());
        }
    }
}

void AudioSystem::update()
{
    if (!mWorld)
    {
        return;
    }

    for (std::size_t i = 0; i < mSources.size(); i++)
    {
        auto e = mWorld->getEntity(mSources[i].second);
        if (e != nullptr)
        {
            ah::Application::getAudio().getAudioSource(mSources[i].first)->setPosition(e->getPosition());
        }
    }
}

} // namespace ses
