#include "Worm.h"
#include <iostream>
#include <cmath>
#include "Math/Vector/Vector.h"

// Inclusion des Components
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/Components/Collider/CircleCollider.h"
#include "GameObject/Components/Collider/TriangleCollider.h"

#include "GameObject/Components/Input/InputAction/InputAction.h"
#include "GameObject/Components/Input/InputAction/Key/Key.h"
#include "GameObject/Components/Sprite/Sprite.h"
#include "GameObject/Components/Rigidbody/Rigidbody.h"

// Inclusion l'entête Resources necéssaire pour instancier les animations
#include "Resources/Resources.h"

// Inclure les Animations
#include "Animations/IdleAnimation.h"
#include "Animations/WalkAnimation.h"
#include "Animations/WinnnerAnimation.h"

// Include les Inputs Action
#include "GameObject/Components/Input/TriggerEvent.h"
#include "Characters/InputActions/MoveAction.h"
#include "Characters/InputActions/JumpAction.h"
#include "Characters/InputActions/FireAction.h"
#include "Characters/InputActions/AimAction.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

// Weapon
#include "Items/Weapons/FireGun/FireGun.h"

#include "Deleguate.h"

Worm::Worm() : Character()
{
    // Instance Animations
    InitAnimations();

    // Init Components
    SquareColliderComponent = std::make_shared<SquareCollider>();
    // SquareColliderComponent = std::make_shared<TriangleCollider>();
    // SquareColliderComponent = std::make_shared<CircleCollider>(50);
    // SquareColliderComponent = std::make_shared<CircleCollider>();
    SquareColliderComponent->SetSize(sf::Vector2f(50, 50));

    SquareColliderComponent->AddCallback(ECollisionEvent::Enter, this, &Worm::OnCollisionEnter);

    DeleguateFire = std::make_shared<Deleguate>();
    DeleguateActionDone = std::make_shared<Deleguate>();

    RigidbodyComponent = std::make_shared<Rigidbody>();
    // RigidbodyComponent->GravityScale = 25;
    RigidbodyComponent->GravityScale = 20;
    // RigidbodyComponent->GravityScale = 5;

    AddComponent(SquareColliderComponent.get());
    AddComponent(CurrentSprite.get());
    AddComponent(RigidbodyComponent.get());

    // Instance Inputs Acitons
    IaMove = std::make_shared<MoveAction>();
    IaJump = std::make_shared<JumpAction>();
    IaFire = std::make_shared<FireAction>();
    IaAim = std::make_shared<AimAction>();

    MaxWalkSpeed = 200;

    // std::cout << SquareColliderComponent->HasLayer(Layers::ALL);
    // std::cout << SquareColliderComponent->HasLayer(Layers::STATIC);

    MaxHealth = 30;
    // MaxHealth = 100;
    CurrentHealth = MaxHealth;
    bIsAlive = true;
    bCanMove = false;
    bCanFire = false;
}

void Worm::Start()
{
    Character::Start();
    SetupBindAction();
}

void Worm::Update(const float DeltaTime)
{
    // if (GetWorld()->GetCharacterControlled().get() == this)
    //     std::cout << RigidbodyComponent->GetVelocity().x << " " << RigidbodyComponent->GetVelocity().y << "\n";

    Character::Update(DeltaTime);
    // AddWorldPosition(AxisMoveValue * MaxWalkSpeed * DeltaTime);
    // AxisMoveValue = sf::Vector2f(0, 0);
    // Worm::Move(DeltaTime);
    // CurrentSprite = WalkA;

    // if (GetWorld()->GetCharacterControlled().get() == this)
    //     std::cout << RigidbodyComponent->GetVelocity().x << " " << RigidbodyComponent->GetVelocity().y << "\n";


}

void Worm::Render(sf::RenderWindow &Window) const
{
    Character::Render(Window);
    DrawAimLine(Window);
}

// PROTECTED

void Worm::SetupBindAction()
{
    InputComponent->BindAction(IaMove, ETriggerEvent::Triggered, this, &Worm::Move);
    InputComponent->BindAction(IaMove, ETriggerEvent::Started, this, &Worm::OnMoveStart);
    InputComponent->BindAction(IaMove, ETriggerEvent::Completed, this, &Worm::OnMoveCompleted);
    InputComponent->BindAction(IaJump, ETriggerEvent::Started, this, &Worm::Jump);
    InputComponent->BindAction(IaFire, ETriggerEvent::Started, this, &Worm::Fire);
    InputComponent->BindAction(IaAim, ETriggerEvent::Triggered, this, &Worm::Aim);
}

float Worm::TakeDamage(const float Damage)
{
    CurrentHealth -= Damage;

    if (CurrentHealth <= 0)
    {
        CurrentHealth = 0;
        bIsAlive = false;
        Destroy();
    }

    return CurrentHealth;
}

void Worm::OnCollisionEnter(GameObject *GameObjectHited)
{
    // SetWorldPosition(sf::Vector2f(300, 200));
    // std::cout << "rara\n";
}

void Worm::OnDestroy()
{
    std::cout << "Worm Destroyed\n";
}

void Worm::InitAnimations()
{
    IdleA = std::make_shared<IdleAnimation>();
    WalkA = std::make_shared<WalkAnimation>();
    WinnnerA = std::make_shared<WinnnerAnimation>();

    // CurrentSprite = WinnnerA;
    // CurrentSprite = WalkA;
    // CurrentSprite = IdleA;
}

// void Worm::Move(float DeltaTime)
void Worm::Move(const sf::Vector2f Value)
{
    if (!bCanMove)
        return;

    // AddWorldPosition(Value * MaxWalkSpeed * GetWorld()->GetWorldDeltaSecond());

    // AxisMoveValue = Value;

    // const sf::Vector2f Force = sf::Vector2f(Value.x, 0) * 500.f;
    // const sf::Vector2f Force = Value * 500.f;
    const sf::Vector2f Force = Value * 1000.f;
    RigidbodyComponent->AddForce(Force);
    // if (movementTimer < 0.5f)
    // {
    //     movementTimer += DeltaTime;
    // }
    // else
    // {
    //     RigidbodyComponent->AddForce(MoveDirection * MaxWalkSpeed);
    // }
}

void Worm::OnMoveStart(const sf::Vector2f Value)
{
    bIsMoving = true;
    bIsAiming = false;
    MoveDirection = Value;
    if (MoveDirection.x > 0)
    {
        AimDirection.x *= (bIsFacingRight ? 1.0f : -1.0f);
        bIsFacingRight = true;
    }
    else if (MoveDirection.x < 0)
    {
        AimDirection.x *= (bIsFacingRight ? -1.0f : 1.0f);
        bIsFacingRight = false;
    }
    movementTimer = 0;
}

void Worm::OnMoveCompleted()
{
    bIsMoving = false;
    bIsAiming = true;
    MoveDirection = sf::Vector2f(0, 0);
}

void Worm::Aim(const sf::Vector2f Value)
{
    if (!bIsAiming)
        return;

    AimAngle += 1.0f * Value.y;
    AimAngle = std::clamp(AimAngle, MIN_AIM_ANGLE, MAX_AIM_ANGLE);
    if (bIsFacingRight)
    {
        AimDirection = sf::Vector2f(cos(AimAngle * M_PI / 180), sin(AimAngle * M_PI / 180));
    }
    else
    {
        AimDirection = sf::Vector2f(-cos(AimAngle * M_PI / 180), sin(AimAngle * M_PI / 180));
    }
}

void Worm::DrawAimLine(sf::RenderWindow &window) const
{
    if (!bIsAiming)
        return;
    // Create a line segment from worm position to aim direction
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = GetWorldPosition();
    line[1].position = GetWorldPosition() + AimDirection * 100.0f; // Change 100.0f to set the magnitude of the vector

    // Set color of the line
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;

    // Draw the line
    window.draw(line);
}

void Worm::Fire()
{
    if (!bCanFire)
        return;

    const sf::Vector2f Location = GetWorldPosition() +  AimDirection * 50.f;
    FireGun *FireGunS = GetWorld()->SpawnGameObject<FireGun>(Location);
    sf::Vector2f force = AimDirection * 20000.f;

    FireGunS->AddForce(force);
    FireGunS->DeleguateOnDestroy->AddCallback(this, &Worm::CallDeleguateActionDone);
    // DeleguateActionDone->Broadcast();

    bCanFire = false;
    bCanMove = false;
}

void Worm::Jump()
{
    RigidbodyComponent->SetVelocity(sf::Vector2f(RigidbodyComponent->GetVelocity().x, 0));
    RigidbodyComponent->AddForce(sf::Vector2f(0, -50000));
}

// PRIVATE

void Worm::CallDeleguateActionDone()
{
    DeleguateActionDone->Broadcast();
}