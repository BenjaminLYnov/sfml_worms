#include "FireGun.h"
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

FireGun::FireGun() : Weapon()
{
    // Init Components
    SquareColliderComponent = std::make_shared<SquareCollider>();
    SquareColliderComponent->SetSize(sf::Vector2f(10, 10));
    SquareColliderComponent->SetCollisionResponse(ECollisionResponse::Overlap);

    RigidbodyComponent = std::make_shared<Rigidbody>();
    RigidbodyComponent->GravityScale = 10;
    RigidbodyComponent->HorizontalDrag = 50;

    Icon = std::make_shared<Sprite>();

    AddComponent(SquareColliderComponent.get());
    AddComponent(RigidbodyComponent.get());

    SquareColliderComponent->AddCallback(ECollisionEvent::Enter, this, &FireGun::OnCollisionEnter);

    DeleguateOnDestroy = std::make_shared<Deleguate>();

    FireGunA = std::make_shared<FireGunAnimation>();
    SwitchAnimation(FireGunA);
}

void FireGun::Start()
{
    Item::Start();
}

void FireGun::Update(const float DeltaTime)
{
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

void FireGun::AddForce(const sf::Vector2f &Force)
{
    RigidbodyComponent->AddForce(Force);
}

// PROTECTED

void FireGun::OnCollisionEnter(GameObject *GameObjectHited)
{
    if (!GameObjectHited)
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

void FireGun::Destroy(GameObject *GameObjectToDestroy)
{

    GameObject::Destroy();
}
