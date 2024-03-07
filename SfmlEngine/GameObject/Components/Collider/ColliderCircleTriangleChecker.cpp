#include "ColliderCircleTriangleChecker.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <cmath>
#include "Math/Vector/Vector.h"

ColliderCircleTriangleChecker::ColliderCircleTriangleChecker()
{
}

// Test de collision entre un cercle et un triangle
HitResult ColliderCircleTriangleChecker::TestCollision(const sf::CircleShape &circle, const sf::ConvexShape &triangle) const
{
    const sf::Vector2f &center = circle.getPosition();
    float radiusSquared = circle.getRadius() * circle.getRadius();
    bool bIsOnCollision = false;

    for (size_t i = 0; i < 3; ++i)
    {
        sf::Vector2f pointA = triangle.getPoint(i);
        sf::Vector2f pointB = triangle.getPoint((i + 1) % 3);

        // Apply rotation to the points
        sf::Transform transform = triangle.getTransform();
        pointA = transform.transformPoint(pointA);
        pointB = transform.transformPoint(pointB);

        // Check Collision Point-Triangle
        if (distanceSquared(center, pointA) < radiusSquared || distanceSquared(center, pointB) < radiusSquared)
        {
            bIsOnCollision = true;
        }

        // Check Collision Edge-Triangle
        sf::Vector2f closestPoint = closestPointOnLine(pointA, pointB, center);
        if (distanceSquared(center, closestPoint) < radiusSquared)
        {
            bIsOnCollision = true;
        }
    }

    return HitResult(bIsOnCollision);
}
// Calcule la distance au carré pour éviter la racine carrée (plus rapide)
float ColliderCircleTriangleChecker::distanceSquared(const sf::Vector2f &a, const sf::Vector2f &b) const
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return dx * dx + dy * dy;
}

// Trouve le point le plus proche sur une arête du triangle par rapport au centre du cercle
sf::Vector2f ColliderCircleTriangleChecker::closestPointOnLine(const sf::Vector2f &a, const sf::Vector2f &b, const sf::Vector2f &p) const
{
    sf::Vector2f ap = p - a;
    sf::Vector2f ab = b - a;
    float magnitudeAB = ab.x * ab.x + ab.y * ab.y;
    float abapProduct = ap.x * ab.x + ap.y * ab.y;
    float distance = abapProduct / magnitudeAB;

    if (distance < 0)
        return a;
    else if (distance > 1)
        return b;
    else
        return a + ab * distance;
}
