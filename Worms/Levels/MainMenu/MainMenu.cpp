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
    AnotherWorm = std::make_shared<Worm>();

    MainWorm->SetName("p1");

    // MainWorm->DeleguateActionDone->AddCallback(this, &MainMenu::Toto);
    // AnotherWorm->DeleguateActionDone->AddCallback(this, &MainMenu::Jojo);

    //MainWorm->DeleguateFire->AddCallback(this, &MainMenu::Toto);

    AnotherWorm->SetName("p2");

    
    AnotherWorm->SetWorldPosition(sf::Vector2f(200, 200));
    //SetCharacterControlled(MainWorm);

	MainWorm->bCanMove = true;
	MainWorm->bCanFire = true;
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
    std::cout << "AnotherWorm \n";
}

void MainMenu::Jojo() {
    std::cout << "MainWorm \n";
}