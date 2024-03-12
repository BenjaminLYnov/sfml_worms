#include "Sound.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

Sound::Sound(const unsigned char *Data, size_t Size)
{
    CueSound = std::make_shared<sf::Sound>();
    Buffer = std::make_shared<sf::SoundBuffer>();

    if (Data && Size)
        LoadFromMemory(Data, Size);
}

Sound::~Sound()
{
}

void Sound::LoadFromMemory(const unsigned char *Data, size_t Size)
{
    if (!Data || !Size)
        return;

    if (!Buffer)
        return;

    Buffer->loadFromMemory(Data, Size);

    if (!CueSound)
        return;

    CueSound->setBuffer(*Buffer);
}

void Sound::Play()
{
    if (!CueSound)
        return;
    CueSound->play();
}

void Sound::Pause()
{
    if (!CueSound)
        return;
    CueSound->pause();
}

void Sound::Stop()
{
    if (!CueSound)
        return;
    CueSound->stop();
}

void Sound::SetLoop(const bool bLoop)
{
    if (!CueSound)
        return;
    CueSound->setLoop(bLoop);
}

bool Sound::IsPlaying() const
{
    if (!CueSound)
        return false;
    return CueSound->getStatus() == sf::Sound::Playing;
}