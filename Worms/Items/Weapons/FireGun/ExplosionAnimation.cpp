#include "ExplosionAnimation.h"
#include "Resources/Resources.h"

ExplosionAnimation::ExplosionAnimation()
{
 if (!LoadTextureFromMemory(pngwing_data, pngwing_size))
        return;

    SetAnimationSpeed(0.1);

    const int RectWidth = 192;
    const int RectHeight = 192;

    for (int i = 0; i < 5; i++)
    {
        const int RectLeft = i * RectWidth;
        AddAnimationFrame(sf::IntRect(RectLeft, 0, RectWidth, RectHeight));
    }

    for (int i = 0; i < 2; i++)
    {
        const int RectLeft = i * RectWidth;
        AddAnimationFrame(sf::IntRect(RectLeft, RectHeight, RectWidth, RectHeight));
    }
}
