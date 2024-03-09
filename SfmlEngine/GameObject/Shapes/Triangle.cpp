#include "Triangle.h"
#include "GameObject/Components/Collider/TriangleCollider.h"

Triangle::Triangle() : GameObject()
{
    TriangleColliderComponent = std::make_shared<TriangleCollider>();
    // TriangleColliderComponent->SetSize(sf::Vector2f(50, 50));
	TriangleColliderComponent->SetMobility(EMobility::Static);
    SetName("Triangle");
    AddComponent(TriangleColliderComponent.get());
}

void Triangle::Start()
{
    GameObject::Start();
}

void Triangle::Update(const float DeltaTime)
{
    GameObject::Update(DeltaTime);
}

void Triangle::Render(sf::RenderWindow &Window) const
{
    GameObject::Render(Window);
}