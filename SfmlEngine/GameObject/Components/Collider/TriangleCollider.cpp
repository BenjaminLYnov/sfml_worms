#include "TriangleCollider.h"
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

TriangleCollider::TriangleCollider(const sf::Vector2f Point1, const sf::Vector2f Point2, sf::Vector2f Point3)
{
    Shape = std::make_shared<sf::ConvexShape>();
    Shape->setPointCount(3);
    SetPoints(Point1, Point2, Point3);

    // Configurer la couleur de remplissage du triangle
    Shape->setOutlineThickness(1);
    Shape->setFillColor(sf::Color::Transparent);
    Shape->setOutlineColor(sf::Color::Green);
}

TriangleCollider::~TriangleCollider()
{
}

void TriangleCollider::Start()
{
    InitCollider();
}

void TriangleCollider::Update(const float DeltaTime)
{

    // Implémentation de la logique de mise à jour spécifique à TriangleCollider
    // UpdatePosition();

    const sf::Vector2f NewPos = GetOwner()->GetWorldPosition() + GetOwner()->GetRelativePosition() + Offset;
    Shape->setPosition(NewPos);
}

void TriangleCollider::Render(sf::RenderWindow &Window)
{
#ifndef NDEBUG
    if (Shape)
        Window.draw(*Shape);
#endif
}

HitResult TriangleCollider::TestCollision(const TriangleCollider &Other) const
{
    return HitResult();
    // return checkCollision(*Shape, *Other.Shape);
}

void TriangleCollider::CancelCollision(ICollider *Other)
{
    TriangleCollider *OtherTriangle = dynamic_cast<TriangleCollider *>(Other);
}

// PRIVATE

void TriangleCollider::SetPoints(const sf::Vector2f Point1, const sf::Vector2f Point2, sf::Vector2f Point3)
{
    Shape->setPoint(0, Point1);
    Shape->setPoint(1, Point2);
    Shape->setPoint(2, Point3);

    // Calculer la largeur du triangle
    float Width = Point1.x;
    if (Point2.x > Width)
        Width = Point2.x;
    if (Point2.x > Width)
        Width = Point2.x;

    if (Width != 0)
        Width /= 2;

    Shape->setOrigin(sf::Vector2f(Width, Width));
}

// Fonction pour calculer la projection d'un polygone sur un axe
std::pair<float, float> TriangleCollider::projectPolygon(const sf::Vector2f &axis, const std::vector<sf::Vector2f> &vertices) const
{
    float min = std::numeric_limits<float>::infinity();
    float max = -std::numeric_limits<float>::infinity();

    for (const auto &vertex : vertices)
    {
        float projection = vertex.x * axis.x + vertex.y * axis.y;
        min = std::min(min, projection);
        max = std::max(max, projection);
    }

    return {min, max};
}

// Fonction pour vérifier si les projections se chevauchent
bool TriangleCollider::overlap(const std::pair<float, float> &projection1, const std::pair<float, float> &projection2) const
{
    return !(projection1.second < projection2.first || projection2.second < projection1.first);
}

// Fonction pour calculer la normale à une arête
sf::Vector2f TriangleCollider::edgeNormal(const sf::Vector2f &start, const sf::Vector2f &end) const
{
    sf::Vector2f edge = end - start;
    return sf::Vector2f(-edge.y, edge.x);
}

// Fonction pour vérifier la collision entre deux triangles
bool TriangleCollider::checkCollision(const sf::ConvexShape &triangle1, const sf::ConvexShape &triangle2) const
{
    std::vector<sf::Vector2f> vertices1, vertices2;

    // Récupérer les vertices des deux triangles
    for (size_t i = 0; i < triangle1.getPointCount(); ++i)
    {
        vertices1.push_back(triangle1.getTransform().transformPoint(triangle1.getPoint(i)));
    }
    for (size_t i = 0; i < triangle2.getPointCount(); ++i)
    {
        vertices2.push_back(triangle2.getTransform().transformPoint(triangle2.getPoint(i)));
    }

    // Vérifier les axes formés par les normales aux arêtes de chaque triangle
    for (size_t i = 0; i < vertices1.size(); ++i)
    {
        sf::Vector2f axis = edgeNormal(vertices1[i], vertices1[(i + 1) % vertices1.size()]);
        if (!overlap(projectPolygon(axis, vertices1), projectPolygon(axis, vertices2)))
        {
            return false; // Pas de collision si aucune projection ne se chevauche sur cet axe
        }
    }

    for (size_t i = 0; i < vertices2.size(); ++i)
    {
        sf::Vector2f axis = edgeNormal(vertices2[i], vertices2[(i + 1) % vertices2.size()]);
        if (!overlap(projectPolygon(axis, vertices2), projectPolygon(axis, vertices1)))
        {
            return false; // Pas de collision si aucune projection ne se chevauche sur cet axe
        }
    }

    // Si toutes les projections se chevauchent, il y a collision
    return true;
}
