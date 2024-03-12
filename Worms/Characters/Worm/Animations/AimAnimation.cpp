#include "AimAnimation.h"
#include "Resources/Resources.h"

AimAnimation::AimAnimation() : Sprite()
{
  if (!LoadTextureFromMemory(wbatfrd_data, wbatfrd_size))
        return;

    SetAnimationSpeed(0.05);

    const int RectWidth = 60;
    const int RectHeight = 52;
    const int RectLeft = 0;

    for (size_t i = 0; i < 32; i++)
    {
        const int RectTop = i * 60;
        AddAnimationFrame(sf::IntRect(RectLeft, RectTop, RectWidth, RectHeight));
    }
}

