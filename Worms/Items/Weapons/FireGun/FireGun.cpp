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
    Animation = std::make_shared<Sprite>(postbox_data, postbox_size);

    AddComponent(SquareColliderComponent.get());
    AddComponent(RigidbodyComponent.get());
    // AddComponent(Icon);
    // AddComponent(Animation);

    SquareColliderComponent->AddCallback(ECollisionEvent::Enter, this, &FireGun::OnCollisionEnter);

    DeleguateOnDestroy = std::make_shared<Deleguate>();
}

void FireGun::Start()
{
    Item::Start();
}

void FireGun::Update(const float DeltaTime)
{
    Item::Update(DeltaTime);
    LifeTime -= DeltaTime;
    if (LifeTime <= 0)
        Destroy();
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
    if (GameObjectHited == GetOwner())
        return;

    std::cout << "FireGun::OnCollisionEnter" << std::endl;


    Worm *WormHited = dynamic_cast<Worm *>(GameObjectHited);
    if (WormHited)
    {
        WormHited->TakeDamage(DammageAmount);
    }

    // GetWorld()->SpawnGameObject<Explosion>();
    Destroy();
}

void FireGun::Destroy(GameObject *GameObjectToDestroy)
{
    DeleguateOnDestroy->Broadcast();
    GameObject::Destroy();
}
