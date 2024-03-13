#include "CannonBall.h"
#include "Resources/Resources.h"
#include "GameObject/Components/Sprite/Sprite.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/Components/Rigidbody/Rigidbody.h"
#include "GameObject/GameObject.h"
#include "iostream"
#include "Deleguate.h"
#include "Characters/Worm/Worm.h"
#include "Explosion.h"
#include "Levels/Party/DeadZone.h"
#include "FireGunAnimation.h"
#include "Math/Vector/Vector.h"

CannonBall::CannonBall() : IProjectile()
{
    FireGunA = std::make_shared<FireGunAnimation>();
    SwitchAnimation(FireGunA);

    RigidbodyComponent->HorizontalDrag = 20;
    RigidbodyComponent->VerticalDrag = 20;
}

void CannonBall::Start()
{
    IProjectile::Start();
}

void CannonBall::Update(const float DeltaTime)
{
    IProjectile::Update(DeltaTime);

    float Rotation = 0;

    if (RigidbodyComponent->GetVelocity().x > 0)
    {
        Rotation = Vector::GetAngleWithXAxis(RigidbodyComponent->GetVelocity());
        AnimationComponent->SetScale(sf::Vector2f(-FireGunSpriteScale, FireGunSpriteScale));
    }
    else
    {
        Rotation = Vector::GetAngleWithXAxis(-RigidbodyComponent->GetVelocity());
        AnimationComponent->SetScale(sf::Vector2f(FireGunSpriteScale, FireGunSpriteScale));
    }
    AnimationComponent->SetRotation(Rotation);

    LifeTime -= DeltaTime;
    if (LifeTime <= 0)
    {
        if (GetOwner())
        {
            Worm *W = dynamic_cast<Worm *>(GetOwner());
            if (W)
                W->CallDeleguateActionDone();
        }
        Destroy();
    }
}

// PROTECTED

void CannonBall::OnCollisionEnter(GameObject *GameObjectHited)
{
    if (!GameObjectHited)
        return;

    SquareColliderComponent->bEnableCollision = false;

    std::shared_ptr<Explosion> Exp = GetWorld()->SpawnGameObject<Explosion>(GetWorldPosition());
    Exp->SetOwner(GetOwner());
    if (GetOwner())
    {
        Worm *W = dynamic_cast<Worm *>(GetOwner());
        if (W)
        {
            W->ExplosionS = Exp;
        }
    }
    Destroy();
}