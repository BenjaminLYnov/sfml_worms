#pragma once

#include "GameObject/Character/Character.h"

class Sprite;
class InputAction;
class Rigidbody;
class SquareCollider;
class CircleCollider;
class TriangleCollider;
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

    // std::shared_ptr<CircleCollider> SquareColliderComponent;
    std::shared_ptr<SquareCollider> SquareColliderComponent;
    // std::shared_ptr<TriangleCollider> SquareColliderComponent;

#pragma region State

    bool bIsAlive;
    bool bIsMoving;
    bool bCanFire;
    bool bCanMove;
    bool bIsAiming;

#pragma endregion State
    int CurrentHealth;

protected:
    std::shared_ptr<Rigidbody> RigidbodyComponent;

    void InitAnimations();

#pragma region InputAction

    virtual void OnMoveStart(const sf::Vector2f Value);
    virtual void OnMoveCompleted();
    virtual void Aim(const sf::Vector2f Value);
    virtual void Jump();
    virtual void Fire();

#pragma endregion

    void SetupBindAction() override;


    void OnDestroy();

    void OnCollisionEnter(GameObject *GameObjectHited);

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
    std::shared_ptr<InputAction> IaAim;

    int MaxHealth;
    int CurrentHealth;
    bool bIsFacingRight;

    sf::Vector2f MoveDirection;

    float AimAngle = 0;
    sf::Vector2f AimDirection = sf::Vector2f(1, 0);
    float movementTimer = 0;

    float M_PI = 3.14159265358979323846;
    const float MIN_AIM_ANGLE = -85;
    const float MAX_AIM_ANGLE = 85;
    const float MOVEMENT_DELAY = 0.1f;

    void Move(const sf::Vector2f Value);
    // void Move(float DeltaTime);
    void DrawAimLine(sf::RenderWindow &Window) const;
    void CallDeleguateActionDone();
};
