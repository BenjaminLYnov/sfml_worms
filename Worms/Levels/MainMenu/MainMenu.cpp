#include "MainMenu.h"
#include <iostream>
#include "Characters/Worm/Worm.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/Components/Rigidbody/Rigidbody.h"

#include "PhysicExo/Vector.h"
#include "PhysicExo/Particle.h"

MainMenu::MainMenu()
{
    // Instance Main Character
    MainWorm = std::make_shared<Worm>();
    std::shared_ptr<Worm> AnotherWorm = std::make_shared<Worm>();

    MainWorm->SetName("p1");
    AnotherWorm->SetName("p2");

    AddGameObject(MainWorm);
    AddGameObject(AnotherWorm);

    MainWorm->SquareColliderComponent->AddCallback(ECollisionEvent::Enter, this, &MainMenu::Enter);
    // MainWorm->SquareColliderComponent->AddCallback(ECollisionEvent::Stay, this, &MainMenu::Stay);
    MainWorm->SquareColliderComponent->AddCallback(ECollisionEvent::Exit, this, &MainMenu::Exit);
    // MainWorm->SquareColliderComponent->AddCallback(ECollisionEvent::Exit, this, &MainMenu::Exit, MainWorm);

    AnotherWorm->SetWorldPosition(sf::Vector2f(200, 200));

    SetCharacterControlled(MainWorm);

    ////////////////////////////////
    // EXO
    // Déclaration particule
    // std::shared_ptr<Particle> MyParticle = std::make_shared<Particle>();
    // std::shared_ptr<Particle> MyParticle2 = std::make_shared<Particle>();

    // AddGameObject(MyParticle);
    // AddGameObject(MyParticle2);

    // MyParticle2->SetWorldPosition(sf::Vector2f(300, 500));
    // MyParticle2->RigidbodyComponent->Gravity = sf::Vector2f(0, 0);
    // MyParticle2->SquareColliderComponent->SetSize(sf::Vector2f(500, 20));
}

void MainMenu::Start()
{
    Level::Start();
}

void MainMenu::Update(const float DeltaTime)
{
    Level::Update(DeltaTime);
}

void MainMenu::Enter()
{
    std::cout << "Enter\n";
}

void MainMenu::Stay()
{
    std::cout << "Stay\n";
}

void MainMenu::Exit()
{
    std::cout << "Exit\n";
}

// void MainMenu::Exit(std::shared_ptr<Worm> w)
// {
//     // std::cout << "Exit\n";
//     w->SetWorldPosition(sf::Vector2f(350, 500));
// }
