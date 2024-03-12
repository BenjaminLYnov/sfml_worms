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
#include "FireGunAnimation.h"
#include "FragmentationBall.h"
#include "BallFragment.h"
#include "Math/Vector/Vector.h"

FragmentationBall::FragmentationBall()
{
    SquareColliderComponent = std::make_shared<SquareCollider>();
    RigidbodyComponent = std::make_shared<Rigidbody>();
    SquareColliderComponent->SetSize(sf::Vector2f(10, 10));
    SquareColliderComponent->SetCollisionResponse(ECollisionResponse::Overlap);

    RigidbodyComponent->GravityScale = 10;
    RigidbodyComponent->HorizontalDrag = 50;

    DammageAmount = 50;

    AddComponent(SquareColliderComponent.get());
    AddComponent(RigidbodyComponent.get());

    SquareColliderComponent->AddCallback(ECollisionEvent::Enter, this, &FragmentationBall::OnCollisionEnter);

    DeleguateOnDestroy = std::make_shared<Deleguate>();

    std::shared_ptr<Sprite> FireGunA = std::make_shared<FireGunAnimation>();
    SwitchAnimation(FireGunA);
}

void FragmentationBall::Start()
{
    IProjectile::Start();
    RigidbodyComponent->AddForce(sf::Vector2f(1000, 0));
}

void FragmentationBall::Update(const float DeltaTime)
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

void FragmentationBall::AddForce(const sf::Vector2f &Force)
{
    RigidbodyComponent->AddForce(Force);
}

void FragmentationBall::OnCollisionEnter(GameObject *GameObjectHited)
{
    IProjectile::OnCollisionEnter(GameObjectHited);
    if (!GameObjectHited || GameObjectHited == GetOwner())
        return;

    // Spawn 5 explosive fragments in random directions
    for (int i = 0; i < 5; i++)
    {
        std::shared_ptr<BallFragment> Fragment =
            GetWorld()->SpawnGameObject<BallFragment>(GetWorldPosition() + sf::Vector2f(0, -20));
        Fragment->SetOwner(GetOwner());
        Fragment->AddForce(sf::Vector2f(0, -10000));
        // Add random force on x axis
        Fragment->AddForce(sf::Vector2f(rand() % 20000 - 10000, 0));
    }
    Destroy();
}

void FragmentationBall::Destroy(GameObject *GameObjectToDestroy)
{
    GameObject::Destroy(GameObjectToDestroy);
}