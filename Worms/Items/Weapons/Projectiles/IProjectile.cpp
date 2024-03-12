#include "IProjectile.h"

// Inclusion des Components
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/Components/Collider/CircleCollider.h"
#include "GameObject/Components/Collider/TriangleCollider.h"

#include "GameObject/Components/Input/InputAction/InputAction.h"
#include "GameObject/Components/Input/InputAction/Key/Key.h"
#include "GameObject/Components/Sprite/Sprite.h"
#include "GameObject/Components/Rigidbody/Rigidbody.h"
#include <Resources/Resources.h>

#include "Deleguate.h"
#include <iostream>

IProjectile::IProjectile()
{
    SquareColliderComponent = std::make_shared<SquareCollider>();
    SquareColliderComponent->SetSize(sf::Vector2f(10, 10));
    SquareColliderComponent->SetCollisionResponse(ECollisionResponse::Overlap);

    RigidbodyComponent = std::make_shared<Rigidbody>();
    RigidbodyComponent->GravityScale = 10;
    RigidbodyComponent->HorizontalDrag = 50;

    AddComponent(SquareColliderComponent.get());
    AddComponent(RigidbodyComponent.get());

    SquareColliderComponent->AddCallback(ECollisionEvent::Enter, this, &IProjectile::OnCollisionEnter);

    DeleguateOnDestroy = std::make_shared<Deleguate>();
}

void IProjectile::Start()
{
    Item::Start();
}

void IProjectile::Update(const float DeltaTime)
{
    Item::Update(DeltaTime);
}

void IProjectile::AddForce(const sf::Vector2f &Force)
{
    RigidbodyComponent->AddForce(Force);
}

void IProjectile::Destroy(GameObject *GameObjectToDestroy)
{
    DeleguateOnDestroy->Broadcast();
    Item::Destroy(GameObjectToDestroy);
}

void IProjectile::OnCollisionEnter(GameObject *GameObjectHited)
{
}
