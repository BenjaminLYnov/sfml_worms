#include "Worm.h"
#include <iostream>

// Inclusion des Components
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/Components/Input/InputAction/InputAction.h"
#include "GameObject/Components/Input/InputAction/Key/Key.h"
#include "GameObject/Components/Sprite/Sprite.h"

// Inclusion l'entête Resources necéssaire pour instancier les animations
#include "Resources/Resources.h"

// Inclure les Animations
#include "Animations/IdleAnimation.h"
#include "Animations/WalkAnimation.h"
#include "Animations/WinnnerAnimation.h"
#include "Animations/JumpAnimation.h"


// Include les Inputs Action
#include "GameObject/Components/Input/TriggerEvent.h"
#include "Characters/InputActions/MoveAction.h"
#include <SFML/Graphics.hpp>

Worm::Worm() : Character()
{
    // Instance Animations
    InitAnimations();

    SquareColliderComponent->SetSize(sf::Vector2f(50, 50));

    AddComponent(CurrentSprite);
    SetWorldPosition(sf::Vector2f(400, 300));

    // Instance Inputs Acitonsqzdsqzdsdzq
    IaMove = std::make_shared<MoveAction>();

    MaxWalkSpeed = 200;
}

void Worm::Start()
{
    Character::Start();

    SetupBindAction();
}

void Worm::Update(const float DeltaTime)
{
    Character::Update(DeltaTime);
}

void Worm::Render(sf::RenderWindow &Window) const
{
    Character::Render(Window);
}

// PROTECTED

void Worm::SetupBindAction()
{
    InputComponent->BindAction(IaMove, ETriggerEvent::Triggered, this, &Worm::Move);

    InputComponent->BindAction(IaMove, ETriggerEvent::Started, this, &Worm::Started);
    InputComponent->BindAction(IaMove, ETriggerEvent::Triggered, this, &Worm::Triggered);
    InputComponent->BindAction(IaMove, ETriggerEvent::Completed, this, &Worm::Completed);
}

void Worm::InitAnimations()
{
    IdleA = std::make_shared<IdleAnimation>();
    WalkA = std::make_shared<WalkAnimation>();
    WinnnerA = std::make_shared<WinnnerAnimation>();
    JumpA = std::make_shared<JumpAnimation>();

    CurrentSprite = JumpA;
}

void Worm::Move(const sf::Vector2f Value)
{
    // std::cout << Value.x << "   " << Value.y << "\n";
    SetInputMovement(Value);
}

void Worm::Started()
{
    CurrentSprite = WalkA;

    std::cout << "started\n";
}

void Worm::Triggered()
{
    std::cout << "Triggered\n";
}

void Worm::Completed()
{
    CurrentSprite = IdleA;

    std::cout << "Completed\n";
}