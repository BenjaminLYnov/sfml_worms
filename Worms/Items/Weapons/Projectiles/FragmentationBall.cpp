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
#include "FragmentationBall.h"
#include "BallFragment.h"

FragmentationBall::FragmentationBall()
{
    SquareColliderComponent = std::make_shared<SquareCollider>();
    RigidbodyComponent = std::make_shared<Rigidbody>();
    SquareColliderComponent->SetSize(sf::Vector2f(10, 10));
    SquareColliderComponent->SetCollisionResponse(ECollisionResponse::Overlap);

    RigidbodyComponent->GravityScale = 10;
    RigidbodyComponent->HorizontalDrag = 50;

    AddComponent(SquareColliderComponent.get());
    AddComponent(RigidbodyComponent.get());
    // AddComponent(Icon);
    // AddComponent(Animation);

    SquareColliderComponent->AddCallback(ECollisionEvent::Enter, this, &FragmentationBall::OnCollisionEnter);

    DeleguateOnDestroy = std::make_shared<Deleguate>();
}

void FragmentationBall::Start()
{
    IProjectile::Start();
    LifeTime = 5;
    DammageAmount = 50;
    RigidbodyComponent->AddForce(sf::Vector2f(1000, 0));
}

void FragmentationBall::Update(const float DeltaTime)
{
    IProjectile::Update(DeltaTime);
    LifeTime -= DeltaTime;
    if (LifeTime <= 0)
        Destroy();
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
        BallFragment *Fragment = GetWorld()->SpawnGameObject<BallFragment>(GetWorldPosition());
        Fragment->AddForce(sf::Vector2f(rand() % 1000, rand() % 1000));
    }
}

void FragmentationBall::Destroy(GameObject *GameObjectToDestroy)
{
    DeleguateOnDestroy->Broadcast();
    IProjectile::Destroy(GameObjectToDestroy);
}