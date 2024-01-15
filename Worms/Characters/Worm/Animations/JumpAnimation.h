#pragma once

#include "GameObject/Components/Sprite/Sprite.h"

class JumpAnimation : public Sprite
{
public:
    JumpAnimation() : Sprite(wjump_data, wjump_size)
    {
        SetAnimationSpeed(0.5);

        const int RectWidth = 60;
        const int RectHeight = 60;
        const int RectLeft = 0;
        const int NbFrames = 10;

        for (size_t i = 0; i < NbFrames; i++)
        {
            const int RectTop = i * 60;
            AddAnimationFrame(sf::IntRect(RectLeft, RectTop, RectWidth, RectHeight));
        }
    }
};
