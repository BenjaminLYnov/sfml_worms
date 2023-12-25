#pragma once

#include "GameObject/Actor/Character/Character.h"

class Sprite;
class InputAction;

class Worm : public Character
{
public:
    Worm();

    void Start() override;

    void Update(const float DeltaTime);

    void Render(sf::RenderWindow &Window) const;

protected:
    void InitAnimations();

private:
    // Sprites Animation
    std::shared_ptr<Sprite> CurrentSprite;
    std::shared_ptr<Sprite> IdleA;
    std::shared_ptr<Sprite> WalkA;
    std::shared_ptr<Sprite> WinnnerA;

    // Input Action
    std::shared_ptr<InputAction> IA_Move;
};
