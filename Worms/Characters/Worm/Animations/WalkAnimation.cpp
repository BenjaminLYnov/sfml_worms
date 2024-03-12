#include "WalkAnimation.h"
#include "Resources/Resources.h"

WalkAnimation::WalkAnimation() : Sprite()
{
    if (!LoadTextureFromMemory(wwalk_data, wwalk_size))
        return;

    SetAnimationSpeed(0.05);

    const int RectWidth = 60;
    const int RectHeight = 52;
    const int RectLeft = 0;

    for (size_t i = 0; i < 15; i++)
    {
        const int RectTop = i * 60;
        AddAnimationFrame(sf::IntRect(RectLeft, RectTop, RectWidth, RectHeight));
    }
}
