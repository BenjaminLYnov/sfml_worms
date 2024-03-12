#include "FireGunAnimation.h"
#include "Resources/Resources.h"

FireGunAnimation::FireGunAnimation()
{
    if (!LoadTextureFromMemory(postbox_data, postbox_size))
        return;

    SetAnimationSpeed(0.1);

    const int RectWidth = 90;
    const int RectHeight = 90;
    const int RectLeft = 0;

    for (int i = 0; i < 2; i++)
    {
        const int RectTop = i * RectHeight;
        AddAnimationFrame(sf::IntRect(RectLeft, RectTop, RectWidth, RectHeight));
    }
}
