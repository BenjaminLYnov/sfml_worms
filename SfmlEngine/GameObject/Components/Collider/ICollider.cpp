#include "ICollider.h"
#include "../Transform/Transform.h"

ICollider::ICollider()
{
    RelativeTransformComponent = new Transform();
}

ICollider::~ICollider()
{
    if (RelativeTransformComponent)
    {
        delete RelativeTransformComponent;    // Libère la mémoire
        RelativeTransformComponent = nullptr; // Bonne pratique pour éviter les pointeurs pendus
    }
}

void ICollider::SetRelativePosition(const sf::Vector2f &position)
{
    if (RelativeTransformComponent)
    {
        RelativeTransformComponent->SetPosition(position);
    }
}

void ICollider::SetRelativeScale(const sf::Vector2f &scale)
{
    if (RelativeTransformComponent)
    {
        RelativeTransformComponent->SetScale(scale);
    }
}

void ICollider::SetRelativeRotation(float rotation)
{
    if (RelativeTransformComponent)
    {
        RelativeTransformComponent->SetRotation(rotation);
    }
}

sf::Vector2f ICollider::GetRelativePosition() const
{
    return RelativeTransformComponent ? RelativeTransformComponent->GetPosition() : sf::Vector2f();
}

sf::Vector2f ICollider::GetRelativeScale() const
{
    return RelativeTransformComponent ? RelativeTransformComponent->GetScale() : sf::Vector2f();
}

float ICollider::GetRelativeRotation() const
{
    return RelativeTransformComponent ? RelativeTransformComponent->GetRotation() : 0.0f;
}
