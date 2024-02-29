#include "Worm.h"
#include <iostream>

// Inclusion des Components
#include "GameObject/Components/Collider/SquareCollider.h"
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
    SquareColliderComponent->SetSize(sf::Vector2f(50, 50));

    DeleguateFire = std::make_shared<Deleguate>();
    DeleguateActionDone = std::make_shared<Deleguate>();

    RigidbodyComponent = std::make_shared<Rigidbody>();
    RigidbodyComponent->GravityScale = 25;
    RigidbodyComponent->GravityScale = 0;

    AddComponent(SquareColliderComponent);
    AddComponent(CurrentSprite);
    AddComponent(RigidbodyComponent);

    SetWorldPosition(sf::Vector2f(400, 300));

    // Instance Inputs Acitons
    IaMove = std::make_shared<MoveAction>();
    IaJump = std::make_shared<JumpAction>();
    IaFire = std::make_shared<FireAction>();

    MaxWalkSpeed = 200;

    // std::cout << SquareColliderComponent->HasLayer(Layers::ALL);
    // std::cout << SquareColliderComponent->HasLayer(Layers::STATIC);

    MaxHealth = 30;
    // MaxHealth = 100;
    CurrentHealth = MaxHealth;
    bIsAlive = true;
    bCanMove = false;
    bCanFire = false;
    bIsControlled = false;
}

void Worm::Start()
{
    Character::Start();
    SetupBindAction();
}

void Worm::Update(const float DeltaTime)
{
    Character::Update(DeltaTime);
    AddWorldPosition(AxisMoveValue * MaxWalkSpeed * DeltaTime);
    AxisMoveValue = sf::Vector2f(0, 0);
    // CurrentSprite = WalkA;
}

void Worm::Render(sf::RenderWindow &Window) const
{
    Character::Render(Window);
}

// PROTECTED

void Worm::SetupBindAction()
{
    InputComponent->BindAction(IaMove, ETriggerEvent::Triggered, this, &Worm::Move);
    InputComponent->BindAction(IaJump, ETriggerEvent::Started, this, &Worm::Jump);
    InputComponent->BindAction(IaFire, ETriggerEvent::Started, this, &Worm::Fire);
}

float Worm::TakeDamage(const float Damage)
{
    CurrentHealth -= Damage;

    if (CurrentHealth <= 0)
    {
        CurrentHealth = 0;
        bIsAlive = false;
        OnDestroy();
    }

    return CurrentHealth;
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

void Worm::Move(const sf::Vector2f Value)
{
    if (!bCanMove)
        return;
    // AxisMoveValue = Value;

    const sf::Vector2f Force = Value * 500.f;
    RigidbodyComponent->AddForce(Force);
}

void Worm::Fire()
{
    if (!bCanFire)
        return;

    const sf::Vector2f Location = GetWorldPosition() + sf::Vector2f(50, 0);
   FireGun *FireGunS = GetWorld()->SpawnGameObject<FireGun>(Location);

    sf::Vector2f force = sf::Vector2f(0.3, -1) * 20000.f;
    // sf::Vector2f force = sf::Vector2f(0.3, -1) * 20000.f;

    FireGunS->AddForce(force);
    FireGunS->SetOwner(this);
    FireGunS->DeleguateOnDestroy->AddCallback(this, &Worm::CallDeleguateActionDone);

    // bCanFire = false;
    // bCanMove = false;
}

void Worm::Jump()
{
    RigidbodyComponent->AddForce(sf::Vector2f(0, -24000));
}

// PRIVATE

void Worm::CallDeleguateActionDone()
{
    DeleguateActionDone->Broadcast();
}