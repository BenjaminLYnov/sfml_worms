#pragma once

#include "GameObject/Components/Sprite/Sprite.h"

class WinnnerAnimation : public Sprite
{
public:
    WinnnerAnimation() : Sprite(wwinner_data, wwinner_size)
    {
        SetAnimationSpeed(0.05);

        const int RectWidth = 60;
        const int RectHeight = 52;
        const int RectLeft = 0;

        for (size_t i = 0; i < 14; i++)
        {
            const int RectTop = i * 60;
            AddAnimationFrame(sf::IntRect(RectLeft, RectTop, RectWidth, RectHeight));
        }
    }
};
