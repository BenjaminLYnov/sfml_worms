#ifndef COLLIDERSQUARETRIANGLECHECKER_H
#define COLLIDERSQUARETRIANGLECHECKER_H

#pragma once
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML
#include <vector>
#include "HitResult.h"

class SquareCollider;
class TriangleCollider;

namespace sf
{
    class RectangleShape;
    class ConvexShape;
    class Shape;
}

class ColliderSquareTriangleChecker
{
public:
    ColliderSquareTriangleChecker();
    HitResult TestCollision(const SquareCollider &rectangleCollider, const TriangleCollider &triangleCollider) const;

private:
    sf::Vector2f normalize(const sf::Vector2f &vector) const;
    std::vector<sf::Vector2f> getRectangleVertices(const sf::RectangleShape &shape) const;
    std::vector<sf::Vector2f> getVertices(const sf::ConvexShape &shape) const;
    std::vector<sf::Vector2f> getVertices(const sf::RectangleShape &shape) const;
    std::vector<sf::Vector2f> getSeparationAxes(const std::vector<sf::Vector2f> &vertices1, const std::vector<sf::Vector2f> &vertices2) const;

    std::pair<float, float> projectPolygon(const sf::Vector2f &axis, const std::vector<sf::Vector2f> &vertices) const;
    float getOverlap(const std::pair<float, float>& projection1, const std::pair<float, float>& projection2) const;

    sf::Vector2f getSideNormal(const sf::Vector2f &p1, const sf::Vector2f &p2) const;
    std::vector<sf::Vector2f> getTriangleNormals(const std::vector<sf::Vector2f> &vertices) const;
    std::vector<sf::Vector2f> getVertices(const sf::Shape &shape) const;
    std::vector<sf::Vector2f> getTriangleSideNormals(const TriangleCollider &triangleCollider) const;
};

#endif