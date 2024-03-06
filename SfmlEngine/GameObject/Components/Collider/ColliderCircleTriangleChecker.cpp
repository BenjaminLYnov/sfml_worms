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

    bool centerInsideTriangle = true;
    for (size_t i = 0; i < 3; ++i)
    {
        sf::Vector2f pointA = triangle.getPoint(i);
        sf::Vector2f pointB = triangle.getPoint((i + 1) % 3);

        // Convertir les points en coordonnées mondiales
        pointA = triangle.getTransform().transformPoint(pointA);
        pointB = triangle.getTransform().transformPoint(pointB);

        // Vérification Collision Coin-Triangle
        if (distanceSquared(center, pointA) < radiusSquared || distanceSquared(center, pointB) < radiusSquared)
        {
            bIsOnCollision = true;
        }

        // Vérification Collision Arête-Triangle
        sf::Vector2f closestPoint = closestPointOnLine(pointA, pointB, center);
        if (distanceSquared(center, closestPoint) < radiusSquared)
        {
            bIsOnCollision = true;
        }

        // Vérification si le centre du cercle est à l'intérieur du triangle
        sf::Vector2f edgeNormal = pointB - pointA;
        sf::Vector2f pointToCenter = center - pointA;
        edgeNormal = sf::Vector2f(-edgeNormal.y, edgeNormal.x); // Normale perpendiculaire
        if (Vector::DotProduct(edgeNormal, pointToCenter) > 0)
        {
            centerInsideTriangle = false;
        }
    }

    return HitResult(true);
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
