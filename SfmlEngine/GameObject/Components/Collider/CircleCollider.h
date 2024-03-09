#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#pragma once

#include "ICollider.h"
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML

// Forward declaration de sf::CircleShape
namespace sf
{
    class CircleShape;
}

class CircleCollider : public ICollider
{
public:
    CircleCollider(const float Radius = 10);
    ~CircleCollider();

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;
    virtual void Render(sf::RenderWindow &Window) override;

    void SetRadius(const float Radius);

    // virtual void UpdatePosition() override;

    std::shared_ptr<sf::CircleShape> Shape; // Représentation graphique du collider pour le rendu

    HitResult TestCollision(const CircleCollider &Other) const;
    // void CancelCollision(const CircleCollider &Other);
    virtual void CancelCollision(ICollider *Other) override;

private:
    sf::Vector2f GetCollisionResolutionVector(sf::CircleShape &circle1, sf::CircleShape &circle2) const;
    sf::Vector2f GetVectorNormal(sf::CircleShape &circle1, sf::CircleShape &circle2) const;

    bool CircleShapeTestCollision(sf::CircleShape &circle1, sf::CircleShape &circle2) const;
    float GetCollisionResolutionDistance(sf::CircleShape &circle1, sf::CircleShape &circle2) const;
};

#endif