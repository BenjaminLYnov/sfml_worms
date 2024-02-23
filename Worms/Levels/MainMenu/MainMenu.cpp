#include "MainMenu.h"
#include <iostream>
#include "Characters/Worm/Worm.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/Components/Rigidbody/Rigidbody.h"

#include "PhysicExo/Vector.h"
#include "PhysicExo/Particle.h"

#include "Items/Weapons/Weapon.h"

#include "Deleguate.h"

MainMenu::MainMenu()
{
    // Instance Main Character
    MainWorm = std::make_shared<Worm>();
    std::shared_ptr<Worm> AnotherWorm = std::make_shared<Worm>();

    MainWorm->SetName("p1");

    MainWorm->DeleguateActionDone->AddCallback(this, &MainMenu::Toto);
    // MainWorm->DeleguateFire->AddCallback(this, &MainMenu::Toto);

    AnotherWorm->SetName("p2");

    AddGameObject(MainWorm);
    AddGameObject(AnotherWorm);
    
    AnotherWorm->SetWorldPosition(sf::Vector2f(200, 200));
    SetCharacterControlled(MainWorm);
}

void MainMenu::Start()
{
    Level::Start();
}

void MainMenu::Update(const float DeltaTime)
{
    Level::Update(DeltaTime);
}

void MainMenu::Toto() {
    std::cout << "joueur a fini son tour \n";
    // std::cout << "joueur a tired une projectile\n";
}