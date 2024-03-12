#include "IdleAnimation.h"
#include "Resources/Resources.h"

IdleAnimation::IdleAnimation() : Sprite()
{
    if (!LoadTextureFromMemory(wselect_data, wselect_size))
        return;

    SetAnimationSpeed(0.1);

    const int RectWidth = 60;
    const int RectHeight = 52;
    const int RectLeft = 0;

    for (size_t i = 0; i < 16; i++)
    {
        const int RectTop = i * 60;
        AddAnimationFrame(sf::IntRect(RectLeft, RectTop, RectWidth, RectHeight));
    }
}
