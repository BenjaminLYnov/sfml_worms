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
    SquareColliderComponent = std::make_shared<SquareCollider>();
    RigidbodyComponent = std::make_shared<Rigidbody>();
    SquareColliderComponent->SetSize(sf::Vector2f(10, 10));
    SquareColliderComponent->SetCollisionResponse(ECollisionResponse::Overlap);

    RigidbodyComponent->GravityScale = 10;
    RigidbodyComponent->HorizontalDrag = 50;

    Icon = std::make_shared<Sprite>();

    AddComponent(SquareColliderComponent.get());
    AddComponent(RigidbodyComponent.get());

    SquareColliderComponent->AddCallback(ECollisionEvent::Enter, this, &CannonBall::OnCollisionEnter);

    DeleguateOnDestroy = std::make_shared<Deleguate>();

    FireGunA = std::make_shared<FireGunAnimation>();
    SwitchAnimation(FireGunA);
}

void CannonBall::Start()
{
    IProjectile::Start();
    LifeTime = 5;
    DammageAmount = 50;
    RigidbodyComponent->AddForce(sf::Vector2f(1000, 0));
}

void CannonBall::Update(const float DeltaTime)
{
    IProjectile::Update(DeltaTime);
    Item::Update(DeltaTime);

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

void CannonBall::AddForce(const sf::Vector2f &Force)
{
    RigidbodyComponent->AddForce(Force);
}

// PROTECTED

void CannonBall::OnCollisionEnter(GameObject *GameObjectHited)
{
    if (!GameObjectHited || GameObjectHited == GetOwner())
        return;

    std::shared_ptr<Explosion> Exp = GetWorld()->SpawnGameObject<Explosion>(GetWorldPosition());
    Exp->SetOwner(GetOwner());
    if (GetOwner())
        {
            Worm *W = dynamic_cast<Worm *>(GetOwner());
            if (W)
                W->ExplosionS = Exp;
        }
    Destroy();
}

void CannonBall::Destroy(GameObject *GameObjectToDestroy)
{
    GameObject::Destroy();
}
