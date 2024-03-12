#include "Explosion.h"
#include "Resources/Resources.h"
#include "GameObject/Components/Sprite/Sprite.h"
#include "GameObject/Components/Collider/CircleCollider.h"
#include "GameObject/GameObject.h"
#include "iostream"
#include "Deleguate.h"
#include "Characters/Worm/Worm.h"
#include "ExplosionAnimation.h"
#include "GameObject/Components/Sprite/AnimatedSprite.h"
#include "Math/Vector/Vector.h"
#include "GameObject/Components/Rigidbody/Rigidbody.h"
#include "GameObject/Components/Sound/Sound.h"

Explosion::Explosion() : Weapon()
{
    CircleColliderComponent = std::make_shared<CircleCollider>();
    CircleColliderComponent->SetRadius(CircleRadius);
    CircleColliderComponent->SetCollisionResponse(ECollisionResponse::Overlap);
    CircleColliderComponent->AddCallback(ECollisionEvent::Stay, this, &Explosion::OnCollisionEnter);

    ExplosionA = std::make_shared<ExplosionAnimation>();
    ExplosionA->SetScale(sf::Vector2f(ExplosionSpriteScale, ExplosionSpriteScale));
    ExplosionA->Animation->SetStopAtLastFrame(true);
    SwitchAnimation(ExplosionA);

    AddComponent(CircleColliderComponent.get());

    SoundExplosion = std::make_shared<Sound>(firered_00AB_data, firered_00AB_size);
    SoundExplosion->Play();
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
        CircleColliderComponent->bEnableCollision = false;
        if (GetOwner() != nullptr)
        {
            Worm *W = dynamic_cast<Worm *>(GetOwner());
            if (W)
                W->CallDeleguateActionDone();
        }
    }
    else
        IndexFrame++;

    if (ExplosionA->Animation->IsOnLastFrame())
        Destroy();
}

void Explosion::OnCollisionEnter(GameObject *GameObjectHited)
{
    if (!GameObjectHited || GameObjectHited == GetOwner())
        return;
    Worm *WormHited = dynamic_cast<Worm *>(GameObjectHited);
    if (WormHited)
    {
        Rigidbody *Rb = WormHited->GetComponent<Rigidbody>();
        if (Rb)
        {
            const sf::Vector2f Direction = Vector::GetDirection(GetWorldPosition(), WormHited->GetWorldPosition());
            Rb->AddForce(Direction * ProjectionForce);
        }
        WormHited->TakeDamage(DammageAmount);
    }
}

void Explosion::Destroy(GameObject *GameObjectToDestroy)
{
    GameObject::Destroy(GameObjectToDestroy);
}

// PRIVATE

void Explosion::InitAnimations()
{
}