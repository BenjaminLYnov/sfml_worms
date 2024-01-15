#pragma once

#include "GameObject/Components/Sprite/Sprite.h"

class IdleAnimation : public Sprite
{
public:
    IdleAnimation() : Sprite(wwalk_data, wwalk_size)
    {
        SetAnimationSpeed(0.05);

        const int RectWidth = 60;
        const int RectHeight = 60;
        const int RectLeft = 0;
        const int NbFrames = 15;


        for (size_t i = 0; i < NbFrames; i++)
        {
            const int RectTop = i * 60;
            AddAnimationFrame(sf::IntRect(RectLeft, RectTop, RectWidth, RectHeight));
        }
    }
};
