#include "Circle.h"
#include "GameObject/Components/Collider/CircleCollider.h"

Circle::Circle() : GameObject()
{
    SetName("Circle");
    CircleColliderComponent = std::make_shared<CircleCollider>();
    CircleColliderComponent->SetRadius(30);
	CircleColliderComponent->SetMobility(EMobility::Static);
    AddComponent(CircleColliderComponent.get());
}

void Circle::Start()
{
    GameObject::Start();
}

void Circle::Update(const float DeltaTime)
{
    GameObject::Update(DeltaTime);
}
