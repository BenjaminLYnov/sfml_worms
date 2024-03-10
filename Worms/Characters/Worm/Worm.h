#pragma once

#include "GameObject/Character/Character.h"

class Sprite;
class InputAction;
class Rigidbody;
class SquareCollider;
class Deleguate;

class Worm : public Character
{

public:
    std::shared_ptr<Deleguate> DeleguateFire;
    std::shared_ptr<Deleguate> DeleguateActionDone;

    Worm();

    void Start() override;
    void Update(const float DeltaTime) override;
    void Render(sf::RenderWindow &Window) const override;

    float TakeDamage(const float Damage) override;

    std::shared_ptr<SquareCollider> SquareColliderComponent;

#pragma region State

    bool bIsControlled;
    bool bIsAlive;
    bool bCanFire;
    bool bCanMove;

#pragma endregion State
    int CurrentHealth;

protected:
    std::shared_ptr<Rigidbody> RigidbodyComponent;

    void InitAnimations();

#pragma region InputAction
    virtual void Move(const sf::Vector2f Value);
    virtual void Jump();
    virtual void Fire();

#pragma endregion
    void SetupBindAction() override;


    void OnDestroy();

private:
    // Sprites Animation
    std::shared_ptr<Sprite> CurrentSprite;
    std::shared_ptr<Sprite> IdleA;
    std::shared_ptr<Sprite> WalkA;
    std::shared_ptr<Sprite> WinnnerA;

    // Input Action
    std::shared_ptr<InputAction> IaMove;
    std::shared_ptr<InputAction> IaJump;
    std::shared_ptr<InputAction> IaFire;

    int MaxHealth;

    void CallDeleguateActionDone();
};
