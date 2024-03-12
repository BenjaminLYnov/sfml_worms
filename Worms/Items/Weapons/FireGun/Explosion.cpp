#include "Explosion.h"
#include "Resources/Resources.h"
#include "GameObject/Components/Sprite/Sprite.h"
#include "GameObject/Components/Collider/CircleCollider.h"
#include "GameObject/GameObject.h"
#include "iostream"
#include "Deleguate.h"
#include "Characters/Worm/Worm.h"

Explosion::Explosion() : Weapon()
{
    CircleColliderComponent = std::make_shared<CircleCollider>();
    CircleColliderComponent->SetRadius(CircleRadius);
    CircleColliderComponent->SetCollisionResponse(ECollisionResponse::Overlap);

    // Icon = std::make_shared<Sprite>();

    AddComponent(CircleColliderComponent.get());
    CircleColliderComponent->AddCallback(ECollisionEvent::Stay, this, &Explosion::OnCollisionEnter);
}

void Explosion::Start()
{
    Item::Start();
}

void Explosion::Update(const float DeltaTime)
{
    Item::Update(DeltaTime);

    if (IndexFrame > 0)
    {
        if (GetOwner())
        {
            Worm *W = dynamic_cast<Worm *>(GetOwner());
            if (W)
                W->CallDeleguateActionDone();
        }
        Destroy();
    }
    else
        IndexFrame++;
}

void Explosion::OnCollisionEnter(GameObject *GameObjectHited)
{
    if (!GameObjectHited)
        return;
    Worm *WormHited = dynamic_cast<Worm *>(GameObjectHited);
    if (WormHited)
    {
        WormHited->TakeDamage(DammageAmount);
    }
}

// private

void Explosion::InitAnimations()
{
}