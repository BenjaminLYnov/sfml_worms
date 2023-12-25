#include "Worm.h"
#include <iostream>

// Inclusion des Components
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/Components/Input/InputAction.h"
#include "GameObject/Components/Sprite/Sprite.h"

// Inclusion l'entête Resources necéssaire pour instancier les animations
#include "Resources/Resources.h"

// Inclure les Animations
#include "Animations/IdleAnimation.h"
#include "Animations/WalkAnimation.h"
#include "Animations/WinnnerAnimation.h"

// Include les Inputs Action
#include "GameObject/Components/Input/TriggerEvent.h"
#include "Characters/InputActions/IAMove.h"

Worm::Worm()
{

    // Instance Animations
    IdleA = std::make_shared<IdleAnimation>();
    WalkA = std::make_shared<WalkAnimation>();
    WinnnerA = std::make_shared<WinnnerAnimation>();

    CurrentSprite = WinnnerA;
    // CurrentSprite = WalkA;
    // CurrentSprite = IdleA;

    SquareColliderComponent->SetSize(sf::Vector2f(50, 50));

    AddComponent(CurrentSprite);
    SetWorldPosition(sf::Vector2f(400, 300));

    // Instance Inputs Acitons
    IA_Move = std::make_shared<IAMove>();

    InputComponent->BindAction(IA_Move, ETriggerEvent::STARTED, []()
                               { std::cout << "Start" << std::endl; });

    InputComponent->BindAction(IA_Move, ETriggerEvent::TRIGGERED, []()
                               { std::cout << "COMPLETED" << std::endl; });

    InputComponent->BindAction(IA_Move, ETriggerEvent::COMPLETED, []()
                               { std::cout << "TRINGGERED" << std::endl; });
}

void Worm::Start()
{
    Character::Start();
}

void Worm::Update(const float DeltaTime)
{
    Character::Update(DeltaTime);

    // InputComponent->Update(DeltaTime);

    // std::cout << "worm update\n";
}

void Worm::Render(sf::RenderWindow &Window) const
{
    Character::Render(Window);
    // std::cout << "worm render\n";
}

void Worm::InitAnimations()
{
}
