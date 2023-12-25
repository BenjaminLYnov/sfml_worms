#pragma once

#include "GameObject/Actor/Character/Character.h"

class Sprite;

// ANIMATIONS
class IdleAnimation;
class WalkAnimation;
class WinnnerAnimation;

// Inputs Action
class IAMove;
class IAJump;

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
    std::shared_ptr<Sprite> CurrentSprite;
    std::shared_ptr<IdleAnimation> IdleA;
    std::shared_ptr<WalkAnimation> WalkA;
    std::shared_ptr<WinnnerAnimation> WinnnerA;

    // std::shared_ptr<In> ;

};
