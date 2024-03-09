#ifndef COLLIDERSQUARECIRCLECHECKER_H
#define COLLIDERSQUARECIRCLECHECKER_H

#pragma once
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML
#include <vector>
#include "HitResult.h"

namespace sf
{
    class RectangleShape;
    class CircleShape;
}

class ColliderSquareCircleChecker
{
public:
    ColliderSquareCircleChecker();
    HitResult TestCollision(const sf::RectangleShape &rectangle, const sf::CircleShape &circle) const;
    sf::Vector2f calculateCorrectionVector(const sf::RectangleShape &rectangle, const sf::CircleShape &circle) const;

private:
    sf::Vector2f getNormalBetweenSquareAndCircle(const sf::RectangleShape &rectangle, const sf::CircleShape &circle) const;
    bool SquareCircleTestCollision(const sf::RectangleShape &rectangle, const sf::CircleShape &circle) const;
    float distance(sf::Vector2f point1, sf::Vector2f point2) const;
    float pointLineDistance(sf::Vector2f point, sf::Vector2f lineStart, sf::Vector2f lineEnd) const;
    sf::Vector2f rotatePoint(sf::Vector2f point, sf::Vector2f pivot, float angle) const;
    std::vector<sf::Vector2f> getRotatedRectanglePoints(const sf::RectangleShape &rectangle) const;
    std::vector<sf::Vector2f> getRotatedRectangleCorners(const sf::RectangleShape &rectangle) const;
    sf::Vector2f closestPointOnSegment(sf::Vector2f segmentStart, sf::Vector2f segmentEnd, sf::Vector2f point) const;
    sf::Vector2f getClosestPointOnRectangle(const sf::RectangleShape &rectangle, const sf::Vector2f &circleCenter) const;
};

#endif