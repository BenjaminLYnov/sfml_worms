#pragma once

#include "GameObject/Components/Sprite/Sprite.h"

class JumpAnimation : public Sprite
{
public:
    JumpAnimation() : Sprite(wflyup_data, wflyup_size)
    {
        SetAnimationSpeed(0.05);

        const int RectWidth = 60;
        const int RectHeight = 60;
        const int RectLeft = 0;
        const int NbFrames = 2;

        for (size_t i = 0; i < NbFrames; i++)
        {
            const int RectTop = i * RectHeight;
            AddAnimationFrame(sf::IntRect(RectLeft, RectTop, RectWidth, RectHeight));
        }
    }
};
