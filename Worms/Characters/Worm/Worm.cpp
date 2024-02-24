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

    AddComponent(SquareColliderComponent);
    AddComponent(CurrentSprite);
    // AddComponent(RigidbodyComponent);

    SetWorldPosition(sf::Vector2f(400, 300));

    // Instance Inputs Acitons
    IaMove = std::make_shared<MoveAction>();
    IaJump = std::make_shared<JumpAction>();
    IaFire = std::make_shared<FireAction>();

    MaxWalkSpeed = 200;

    // std::cout << SquareColliderComponent->HasLayer(Layers::ALL);
    // std::cout << SquareColliderComponent->HasLayer(Layers::STATIC);

	Health = 100;
    bIsAlive = true;
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

int Worm::TakeDamage(const int Damage)
{
    Health -= Damage;

    if(Health < 0)
	{
		Health = 0;
        bIsAlive = false;
	}

    return Health;
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
    AxisMoveValue = Value;
    // SetInputMovement(Value);
}

void Worm::Fire()
{
    const sf::Vector2f Location = GetWorldPosition() + sf::Vector2f(50, 0);
	std::shared_ptr<FireGun> FireGunS = SpawnGameObject<FireGun>(Location);
    // sf::Vector2f force = sf::Vector2f(1, -1) * 80000.f;
    sf::Vector2f force = sf::Vector2f(0.3, -1) * 20000.f;
    // sf::Vector2f force = sf::Vector2f(1, -1) * 30000.f;
    FireGunS->AddForce(force);
    FireGunS->SetOwner(this);

    // DeleguateFire->Broadcast();
    FireGunS->DeleguateOnDestroy->AddCallback(this, &Worm::CallDeleguateActionDone);
}

void Worm::Jump()
{
    // Destroy();
    // std::cout << "Jump\n";

    // SpawnGameObject<Worm>();

    // auto GameObjects = GetAllGameObjectByClass<Worm>();
    // std::vector<std::shared_ptr<GameObject>> GameObjects = GetAllGameObjects();

    // std::cout << GameObjects.size();
    // GameObjects[1]->SetRelativePosition(sf::Vector2f(400, 400));
    // GameObjects[1]->SetWorldPosition(sf::Vector2f(400, 400));

}

// PRIVATE

void Worm::CallDeleguateActionDone() {
    DeleguateActionDone->Broadcast();
}