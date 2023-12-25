#include "Worm.h"
#include <iostream>
#include "GameObject/Components/Sprite/Sprite.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "Resources/Resources.h"

#include "Animations/IdleAnimation.h"
#include "Animations/WalkAnimation.h"
#include "Animations/WinnnerAnimation.h"

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
}

void Worm::Start()
{
    Character::Start();
    // Ajoute le Sprite comme composant
    // std::cout << "worm start\n";
}

void Worm::Update(const float DeltaTime)
{
    Character::Update(DeltaTime);

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
