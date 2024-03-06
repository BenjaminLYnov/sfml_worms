#ifndef COLLIDERCIRCLETRIANGLECHECKER_H
#define COLLIDERCIRCLETRIANGLECHECKER_H

#pragma once
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML
#include "HitResult.h"

namespace sf
{
    class CircleShape;
    class ConvexShape;
}

class ColliderCircleTriangleChecker
{
public:
    ColliderCircleTriangleChecker();

    HitResult TestCollision(const sf::CircleShape &circle, const sf::ConvexShape &triangle) const;

private:
    float distanceSquared(const sf::Vector2f &a, const sf::Vector2f &b) const;
    sf::Vector2f closestPointOnLine(const sf::Vector2f &a, const sf::Vector2f &b, const sf::Vector2f &p) const;
};

#endif