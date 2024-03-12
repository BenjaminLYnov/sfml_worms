#include "CannonBall.h"
#include "Resources/Resources.h"
#include "GameObject/Components/Sprite/Sprite.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/Components/Collider/CircleCollider.h"
#include "GameObject/Components/Rigidbody/Rigidbody.h"
#include "GameObject/GameObject.h"
#include "iostream"
#include "Deleguate.h"
#include "Characters/Worm/Worm.h"
#include "Levels/Graph/Cell.h"
#include "Explosion.h"
#include "BallFragment.h"

BallFragment::BallFragment()
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

    SquareColliderComponent->AddCallback(ECollisionEvent::Enter, this, &BallFragment::OnCollisionEnter);

    DeleguateOnDestroy = std::make_shared<Deleguate>();
}

void BallFragment::Start()
{
    IProjectile::Start();
    LifeTime = 5;
    DammageAmount = 50;
    RigidbodyComponent->AddForce(sf::Vector2f(1000, 0));
}

void BallFragment::Update(const float DeltaTime)
{
    IProjectile::Update(DeltaTime);
    LifeTime -= DeltaTime;
    if (LifeTime <= 0)
        Destroy();
}

void BallFragment::AddForce(const sf::Vector2f &Force)
{
    RigidbodyComponent->AddForce(Force);
}

void BallFragment::OnCollisionEnter(GameObject *GameObjectHited)
{
    IProjectile::OnCollisionEnter(GameObjectHited);
    if (!GameObjectHited || GameObjectHited == GetOwner())
        return;
    Cell *C = dynamic_cast<Cell *>(GameObjectHited);
    Worm *W = dynamic_cast<Worm *>(GameObjectHited);
    if (!C && !W)
    {
        return;
    }

    // Spawn small explosion
    std::shared_ptr<Explosion>
        Exp = GetWorld()->SpawnGameObject<Explosion>(GetWorldPosition());
    Exp->GetComponent<CircleCollider>()->SetRadius(15);
    Exp->SetOwner(GetOwner());
    Destroy();
}

void BallFragment::Destroy(GameObject *GameObjectToDestroy)
{
    GameObject::Destroy(GameObjectToDestroy);
}