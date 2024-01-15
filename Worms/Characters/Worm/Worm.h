#pragma once

#include "GameObject/Actor/Character/Character.h"

class Sprite;
class InputAction;

class Worm : public Character
{
public:
    Worm();

    void Start() override;

    void Update(const float DeltaTime) override;

    void Render(sf::RenderWindow &Window) const override;

protected:
    void InitAnimations();

    virtual void Move(const sf::Vector2f Value);
    virtual void Started();
    virtual void Triggered();
    virtual void Completed();

    void SetupBindAction() override;

private:
    // Sprites Animation
    std::shared_ptr<Sprite> CurrentSprite;
    std::shared_ptr<Sprite> IdleA;
    std::shared_ptr<Sprite> WalkA;
    std::shared_ptr<Sprite> WinnnerA;
    std::shared_ptr<Sprite> JumpA;


    // Input Action
    std::shared_ptr<InputAction> IaMove;
};
