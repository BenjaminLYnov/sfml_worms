#include "Transform.h"

Transform::Transform()
    : Position(0.f, 0.f), Scale(1.f, 1.f), Rotation(0.f)
{
}

void Transform::Start()
{
}

void Transform::Update(const float DeltaTime)
{
}

void Transform::SetPosition(const sf::Vector2f &NewPosition)
{
    Position = NewPosition;
}

void Transform::SetScale(const sf::Vector2f &NewScale)
{
    Scale = NewScale;
}

void Transform::SetRotation(const float NewRotation)
{
    Rotation = NewRotation;
}

const sf::Vector2f &Transform::GetPosition() const
{
    return Position;
}

const sf::Vector2f &Transform::GetScale() const
{
    return Scale;
}

float Transform::GetRotation() const
{
    return Rotation;
}
