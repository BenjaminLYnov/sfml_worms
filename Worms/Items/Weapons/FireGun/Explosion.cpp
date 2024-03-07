#include "Explosion.h"
#include "Resources/Resources.h"
#include "GameObject/Components/Sprite/Sprite.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/GameObject.h"
#include "iostream"
#include "Deleguate.h"
#include "Characters/Worm/Worm.h"

Explosion::Explosion() : Weapon()
{
    SquareColliderComponent = std::make_shared<SquareCollider>();
    SquareColliderComponent->SetSize(sf::Vector2f(10, 10));
    SquareColliderComponent->SetCollisionResponse(ECollisionResponse::Overlap);

    Icon = std::make_shared<Sprite>();

    AddComponent(SquareColliderComponent.get());

    SquareColliderComponent->AddCallback(ECollisionEvent::Stay, this, &Explosion::OnCollisionStay);
}

void Explosion::Start()
{
    Item::Start();
}

void Explosion::Update(const float DeltaTime)
{
    Item::Update(DeltaTime);
}

void Explosion::OnCollisionStay(GameObject *GameObjectHited)
{
    if (!GameObjectHited)
        return;
    if (GameObjectHited == GetOwner())
        return;
}

// private

void Explosion::InitAnimations()
{
}