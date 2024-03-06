#include "ColliderChecker.h"
#include <iostream>
#include "SquareCollider.h"
#include "CircleCollider.h"
#include "TriangleCollider.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>
#include "ColliderSquareCircleChecker.h"
#include "ColliderSquareTriangleChecker.h"
#include "ColliderCircleTriangleChecker.h"

template <>
HitResult ColliderChecker::TestCollision<SquareCollider>(const SquareCollider &Collider1, const SquareCollider &Collider2)
{
    return Collider1.TestCollision(Collider2);
}

template <>
HitResult ColliderChecker::TestCollision<CircleCollider>(const CircleCollider &Collider1, const CircleCollider &Collider2)
{
    return Collider1.TestCollision(Collider2);
}

// template <>
// bool ColliderChecker::TestCollision<TriangleCollider>(const TriangleCollider &Collider1, const TriangleCollider &Collider2)
// {
//     return Collider1.TestCollision(Collider2);
// }

template <>
HitResult ColliderChecker::TestCollision<SquareCollider, CircleCollider>(const SquareCollider &Collider1, const CircleCollider &Collider2)
{
    ColliderSquareCircleChecker Checker = ColliderSquareCircleChecker();
    return Checker.TestCollision(*Collider1.Shape, *Collider2.Shape);
}

template <>
HitResult ColliderChecker::TestCollision<SquareCollider, TriangleCollider>(const SquareCollider &Collider1, const TriangleCollider &Collider2)
{
    ColliderSquareTriangleChecker Checker = ColliderSquareTriangleChecker();
    return Checker.TestCollision(Collider1, Collider2);
}

// template <>
// bool ColliderChecker::TestCollision<CircleCollider, TriangleCollider>(const CircleCollider &Collider1, const TriangleCollider &Collider2)
// {
//     ColliderCircleTriangleChecker Checker = ColliderCircleTriangleChecker();
//     return Checker.TestCollision(*Collider1.Shape, *Collider2.Shape);
// }

// template <>
// sf::Vector2f ColliderChecker::GetCancelCollision<SquareCollider, CircleCollider>(const SquareCollider &Collider1, const CircleCollider &Collider2)
// {
//     ColliderSquareCircleChecker Checker = ColliderSquareCircleChecker();
//     return -Checker.calculateCorrectionVector(*Collider1.Shape, *Collider2.Shape);
// }
