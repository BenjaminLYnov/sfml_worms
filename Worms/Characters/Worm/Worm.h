#pragma once

#include "GameObject/Character/Character.h"

class Sprite;
class InputAction;
class Rigidbody;
class SquareCollider;

class Worm : public Character
{
public:
    Worm();

    void Start() override;

    void Update(const float DeltaTime) override;

    void Render(sf::RenderWindow &Window) const override;

    std::shared_ptr<SquareCollider> SquareColliderComponent;

protected:
    std::shared_ptr<Rigidbody> RigidbodyComponent;

    void InitAnimations();

    virtual void Move(const sf::Vector2f Value);
    virtual void Started();
    virtual void Triggered();
    virtual void Completed();

    virtual void Jump();

    void SetupBindAction() override;

private:
    // Sprites Animation
    std::shared_ptr<Sprite> CurrentSprite;
    std::shared_ptr<Sprite> IdleA;
    std::shared_ptr<Sprite> WalkA;
    std::shared_ptr<Sprite> WinnnerA;

    // Input Action
    std::shared_ptr<InputAction> IaMove;
    std::shared_ptr<InputAction> IaJump;
};
