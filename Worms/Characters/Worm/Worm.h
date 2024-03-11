#pragma once

#include "GameObject/Character/Character.h"

class Sprite;
class InputAction;
class Rigidbody;
class SquareCollider;
class CircleCollider;
class TriangleCollider;
class Deleguate;
class Text;
class Team;
class FireGun;

class Worm : public Character
{

public:
    std::shared_ptr<Deleguate> DeleguateFire;
    std::shared_ptr<Deleguate> DeleguateActionDone;

    Worm();

    void Start() override;
    void Update(const float DeltaTime) override;
    void Render(sf::RenderWindow &Window) const override;

    void Destroy(GameObject *GameObjectToDestroy = nullptr) override;
    float TakeDamage(const float Damage) override;

    void CallDeleguateActionDone();

    std::shared_ptr<SquareCollider> SquareColliderComponent;

    std::shared_ptr<Text> TextName;
    std::shared_ptr<Text> TextHp;

    std::shared_ptr<Team> Team;

    float SpeedMoveView = 500;
    float SpeedZoom = 0.5;

#pragma region State

    bool bIsAlive;
    bool bIsMoving;
    bool bCanFire;
    bool bCanMove;
    bool bCanJump;
    bool bIsAiming;

#pragma endregion State
    int CurrentHealth;

    std::shared_ptr<Rigidbody> RigidbodyComponent;

protected:
    void InitAnimations();

#pragma region InputAction

    virtual void OnMoveStart(const sf::Vector2f Value);
    virtual void OnMoveCompleted();
    virtual void Aim(const sf::Vector2f Value);
    virtual void Jump();
    virtual void Fire();
    virtual void MoveViewport(const sf::Vector2f Value);
    virtual void ZoomViewport(const sf::Vector2f Value);
    virtual void ResetViewport();
    virtual void RestartParty();
    virtual void LoadGraphEdition();

#pragma endregion

    void SetupBindAction() override;

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
    std::shared_ptr<InputAction> IaMoveViewport;
    std::shared_ptr<InputAction> IaZoomViewport;
    std::shared_ptr<InputAction> IaResetViewport;
    std::shared_ptr<InputAction> IaRestartParty;
    std::shared_ptr<InputAction> IaLoadGraphEdition;

    // Weapon
    FireGun *FireGunS = nullptr;

    int MaxHealth;
    bool bIsFacingRight;

    sf::Vector2f JumpForce = sf::Vector2f(40000, -70000);

    sf::Vector2f MoveDirection = sf::Vector2f(1, 0);
    ;

    float AimAngle = 0;
    sf::Vector2f AimDirection = sf::Vector2f(1, 0);

    float movementTimer = 0;

    float M_PI = 3.14159265358979323846;
    const float MIN_AIM_ANGLE = -85;
    const float MAX_AIM_ANGLE = 85;
    const float MOVEMENT_DELAY = 0.1f;

    void Move(const sf::Vector2f Value);
    void DrawAimLine(sf::RenderWindow &Window) const;
};
