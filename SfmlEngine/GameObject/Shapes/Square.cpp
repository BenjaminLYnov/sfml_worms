#include "Square.h"
#include "GameObject/Components/Collider/SquareCollider.h"

Square::Square() : GameObject()
{
    SquareColliderComponent = std::make_shared<SquareCollider>();
    SquareColliderComponent->SetSize(sf::Vector2f(50, 50));
    SetName("square");
    AddComponent(SquareColliderComponent);
}

void Square::Start()
{
    GameObject::Start();
}

void Square::Update(const float DeltaTime)
{
    GameObject::Update(DeltaTime);
}

void Square::Render(sf::RenderWindow &Window) const
{
    GameObject::Render(Window);
}