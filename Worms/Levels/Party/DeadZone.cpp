#include "DeadZone.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "Characters/Worm/Worm.h"

DeadZone::DeadZone()
{
    SquareColliderComponent = std::make_shared<SquareCollider>();
    SquareColliderComponent->SetSize(sf::Vector2f(5000, 200));
    SquareColliderComponent->AddCallback(ECollisionEvent::Enter, this, &DeadZone::OnCollisionEnter);
    AddComponent(SquareColliderComponent.get());
}

void DeadZone::Start()
{
    GameObject::Start();
}

// PRIVATE
void DeadZone::OnCollisionEnter(GameObject *GameObjectHited)
{
    Worm *W = dynamic_cast<Worm *>(GameObjectHited);
    if (W)
    {
        W->CallDeleguateActionDone();
        W->Destroy();
    }
}