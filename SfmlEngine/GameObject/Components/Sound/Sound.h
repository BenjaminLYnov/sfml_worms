#ifndef SOUND_H
#define SOUND_H

#pragma once

#include <memory>

namespace sf
{
    class SoundBuffer;
    class Sound;
}

class Sound
{
public:
    Sound(const unsigned char *Data = nullptr, size_t Size = 0);
    ~Sound();

    void LoadFromMemory(const unsigned char *Data = nullptr, size_t Size = 0);
   
    void Play();
    void Pause();
    void Stop();
    void SetLoop(const bool bLoop);

    bool IsPlaying() const;

private:
    std::shared_ptr<sf::SoundBuffer> Buffer;
    std::shared_ptr<sf::Sound> CueSound;
};

#endif