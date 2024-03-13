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

class Explosion;
class Sound;
class CannonBall;
class FragmentationBall;
class ProgressBar;

// Animations
class IdleAnimation;
class WalkAnimation;
class AimAnimation;
class WinAnimation;
class JumpAnimation;

class Worm : public Character
{

public:
    std::shared_ptr<Deleguate> DeleguateFire;
    std::shared_ptr<Deleguate> DeleguateActionDone;
    std::shared_ptr<Deleguate> DeleguateDeath;

    Worm();

    void Start() override;
    void Update(const float DeltaTime) override;
    void Render(sf::RenderWindow &Window) const override;

    void Destroy(GameObject *GameObjectToDestroy = nullptr) override;
    float TakeDamage(const float Damage) override;

    void SetWinAnimation();
    void CallDeleguateActionDone();

    float GetShootForce();

    std::shared_ptr<SquareCollider> SquareColliderComponent;

    std::shared_ptr<Text> TextName;
    std::shared_ptr<Text> TextHp;

    std::shared_ptr<Team> Team;

    float SpeedMoveView = 500;
    float SpeedZoom = 0.5;

    // Weapon
    std::shared_ptr<Explosion> ExplosionS;
    std::shared_ptr<FragmentationBall> FragmentationBallS;
    std::shared_ptr<CannonBall> CannonBallS;

    bool bIsSecondWeaponEquipped;

#pragma region State

    bool bIsAlive;
    bool bIsMoving;
    bool bCanFire;
    bool bCanMove;
    bool bCanJump;
    bool bIsAiming;
    bool bWon;

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
    virtual void ChangeWeapon();
    virtual void OnFireTriggered();
    virtual void OnFireCompleted();
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
    std::shared_ptr<IdleAnimation> IdleA;
    std::shared_ptr<WalkAnimation> WalkA;
    std::shared_ptr<AimAnimation> AimA;
    std::shared_ptr<WinAnimation> WinA;
    std::shared_ptr<JumpAnimation> JumpA;

    // Input Action
    std::shared_ptr<InputAction> IaMove;
    std::shared_ptr<InputAction> IaJump;
    std::shared_ptr<InputAction> IaChangeWeapon;
    std::shared_ptr<InputAction> IaFire;
    std::shared_ptr<InputAction> IaAim;
    std::shared_ptr<InputAction> IaMoveViewport;
    std::shared_ptr<InputAction> IaZoomViewport;
    std::shared_ptr<InputAction> IaResetViewport;
    std::shared_ptr<InputAction> IaRestartParty;
    std::shared_ptr<InputAction> IaLoadGraphEdition;

    std::shared_ptr<Sound> SoundJump;
    std::shared_ptr<Sound> SoundShoot;

    std::shared_ptr<ProgressBar> PB;

    int MaxHealth;
    bool bIsFacingRight;

    sf::Vector2f JumpForce = sf::Vector2f(20000, -50000);

    sf::Vector2f MoveDirection = sf::Vector2f(1, 0);

    float ShootForce;
    float ShootForceTimerMax = 1.0f;
    float ShootForceMax = 100000;
    float ShootForceMin = 1000;
    float ShootForceTimer = 0;
    float ShootForceSpeedIncrease = 30000;
    bool bIncreaseShootForce = true;
    bool bIsIncreasingShootForce = false;

    float AimAngle = 0;
    sf::Vector2f AimDirection = sf::Vector2f(1, 0);

    float movementTimer = 0;

    float AimSpeed = 100;
    float MaxWalkSpeed = 15000;

    float M_PI = 3.14159265358979323846;
    const float MIN_AIM_ANGLE = -82;
    const float MAX_AIM_ANGLE = 82;
    const float MOVEMENT_DELAY = 0.1f;

    void Move(const sf::Vector2f Value);
    void DrawAimLine(sf::RenderWindow &Window) const;

    int DegreeToFrame(float Degree) const;
};
