#include "GameObject/Components/Sprite/Sprite.h"

class CharacterRun : public Sprite
{
public:
    CharacterRun(const unsigned char *Data = nullptr, size_t Size = 0)
    {
        // Crée un std::shared_ptr pour un nouvel objet Sprite
        // SetAnimationSpeed(0.05);

        // const int RectWidth = 24;
        // const int RectHeight = 28;
        // const int RectLeft = 19;

        // for (size_t i = 0; i < 36; i++)
        // {
        //     const int RectTop = 15 + i * 60;
        //     AddAnimationFrame(sf::IntRect(RectLeft, RectTop, RectWidth, RectHeight));
        // }
    }
};
