#include "CircleCollider.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Math/Vector/Vector.h"
#include <iostream>
#include "HitResult.h"

CircleCollider::CircleCollider(const float Radius) : ICollider()
{
    Shape = std::make_shared<sf::CircleShape>();
    SetRadius(Radius);

    Shape->setFillColor(sf::Color::Transparent);
    Shape->setOutlineThickness(1);
    Shape->setOutlineColor(sf::Color::Green);
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Start()
{
    // Implémentation de la logique de démarrage spécifique à CircleCollider
    InitCollider();
}

void CircleCollider::Update(const float DeltaTime)
{
    // Implémentation de la logique de mise à jour spécifique à CircleCollider
    // UpdatePosition();

    const sf::Vector2f NewPos = GetOwner()->GetWorldPosition() + GetOwner()->GetRelativePosition() + Offset;
    Shape->setPosition(NewPos);
}

void CircleCollider::Render(sf::RenderWindow &Window)
{
#ifndef NDEBUG
    if (Shape)
        Window.draw(*Shape);
#endif
}

HitResult CircleCollider::TestCollision(const CircleCollider &Other) const
{
    // Calculer la distance entre les centres des deux cercles
    float dist = Vector::GetDistance(Shape->getPosition(), Other.Shape->getPosition());

    // Calculer la somme des rayons
    float sumOfRadii = Shape->getRadius() + Other.Shape->getRadius();

    // Si la distance est inférieure ou égale à la somme des rayons, il y a collision
    const bool bIsOnCollision = dist <= sumOfRadii;

    if (!bIsOnCollision)
        return HitResult(false);

    const sf::Vector2f Normal = Vector::GetDirection(Other.Shape->getPosition(), Shape->getPosition());

    // Distance de pénétration
    const float Distance = sumOfRadii - dist;

    return HitResult(bIsOnCollision, Normal, Distance);
}

void CircleCollider::SetRadius(const float Radius)
{
    Shape->setRadius(Radius);
    Shape->setOrigin(Radius, Radius);
}

// void CircleCollider::CancelCollision(const CircleCollider &Other)
void CircleCollider::CancelCollision(ICollider *Other)
{
    CircleCollider *OtherCircle = dynamic_cast<CircleCollider *>(Other);

    sf::CircleShape circle1 = *Shape;
    sf::CircleShape circle2 = *OtherCircle->Shape;

    float dist = Vector::GetDistance(circle1.getPosition(), circle2.getPosition());
    float sumOfRadii = circle1.getRadius() + circle2.getRadius();
    sf::Vector2f CancelVector;

    if (dist > sumOfRadii)
        return;

    float overlap = sumOfRadii - dist; // Calculer le chevauchement
    overlap = std::ceil(overlap) + 0;
    sf::Vector2f direction = circle2.getPosition() - circle1.getPosition();
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= magnitude; // Normaliser le vecteur direction
    CancelVector = direction * overlap;
    // std::cout << overlap << "\n";

    // std::cout << CancelVector.x << "   " << CancelVector.y << "\n";

    GetOwner()->AddWorldPosition(-CancelVector);
}

// PRIVATE

// Fonction pour ajuster la position du deuxième cercle pour éviter le chevauchement
sf::Vector2f CircleCollider::GetCollisionResolutionVector(sf::CircleShape &circle1, sf::CircleShape &circle2) const
{
    float dist = Vector::GetDistance(circle1.getPosition(), circle2.getPosition());
    float sumOfRadii = circle1.getRadius() + circle2.getRadius();
    sf::Vector2f CancelVector = sf::Vector2f(0, 0);

    if (dist > sumOfRadii)
        return CancelVector;

    float overlap = sumOfRadii - dist; // Calculer le chevauchement
    overlap = std::ceil(overlap) + 0;
    sf::Vector2f direction = circle2.getPosition() - circle1.getPosition();
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= magnitude; // Normaliser le vecteur direction
    CancelVector = direction * overlap;

    return CancelVector;
}

sf::Vector2f CircleCollider::GetVectorNormal(sf::CircleShape &circle1, sf::CircleShape &circle2) const
{
    return sf::Vector2f(0, 0);
}

bool CircleCollider::CircleShapeTestCollision(sf::CircleShape &circle1, sf::CircleShape &circle2) const
{
    // Calculer la distance entre les centres des deux cercles
    float dist = Vector::GetDistance(circle1.getPosition(), circle2.getPosition());

    // Calculer la somme des rayons
    float sumOfRadii = circle1.getRadius() + circle2.getRadius();

    // Si la distance est inférieure ou égale à la somme des rayons, il y a collision
    return dist <= sumOfRadii;
}

float CircleCollider::GetCollisionResolutionDistance(sf::CircleShape &circle1, sf::CircleShape &circle2) const
{
    // Calculer la distance entre les centres des deux cercles
    float dist = Vector::GetDistance(circle1.getPosition(), circle2.getPosition());

    // Calculer la somme des rayons
    float sumOfRadii = circle1.getRadius() + circle2.getRadius();

    // Si la distance est inférieure ou égale à la somme des rayons, il y a collision
    return dist <= sumOfRadii;
}
