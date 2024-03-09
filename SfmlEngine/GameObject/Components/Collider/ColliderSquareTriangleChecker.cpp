#include "ColliderSquareTriangleChecker.h"
#include "SquareCollider.h"
#include "TriangleCollider.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <cmath>
#include <limits>
#include <vector>
#include <iostream>

// Définissez ici les fonctions utilitaires telles que getVertices, findNormal, projectPolygon, etc.

ColliderSquareTriangleChecker::ColliderSquareTriangleChecker() {}

HitResult ColliderSquareTriangleChecker::TestCollision(const SquareCollider &rectangleCollider, const TriangleCollider &triangleCollider) const
{
   // Extraire les vertices des colliders
    auto rectangleVertices = getVertices(*rectangleCollider.Shape);
    auto triangleVertices = getVertices(*triangleCollider.Shape);

    // Déterminer les axes de séparation à tester pour les côtés du rectangle
    std::vector<sf::Vector2f> axesRect = getSeparationAxes(rectangleVertices, triangleVertices);

    // Variables pour stocker l'axe de séparation minimal et son overlap minimum
    sf::Vector2f minSeparationAxis;
    float minOverlap = std::numeric_limits<float>::max();

    // Vérifier le chevauchement sur tous les axes
    for (const auto &axis : axesRect)
    {
        auto projection1 = projectPolygon(axis, rectangleVertices);
        auto projection2 = projectPolygon(axis, triangleVertices);
        float overlap = getOverlap(projection1, projection2);
        if (overlap <= 0.0f)
        {
            return HitResult(); // Pas de collision si un axe de séparation est trouvé
        }
        else if (overlap < minOverlap)
        {
            minOverlap = overlap;
            minSeparationAxis = axis;
        }
    }

    sf::Vector2f Normal = minSeparationAxis;

    // Collision détectée, retourner l'axe de séparation minimal
    return HitResult(true, Normal, minOverlap);
}

//  PRIVATE

sf::Vector2f ColliderSquareTriangleChecker::normalize(const sf::Vector2f &vector) const
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length == 0)
        return sf::Vector2f(0, 0); // Évite la division par zéro
    return vector / length;
}

// Vous devez implémenter getVertices, getSeparationAxes, projectPolygon, et overlap comme décrit précédemment.
std::vector<sf::Vector2f> ColliderSquareTriangleChecker::getRectangleVertices(const sf::RectangleShape &shape) const
{
    std::vector<sf::Vector2f> vertices;
    sf::Transform transform = shape.getTransform();
    vertices.push_back(transform.transformPoint(sf::Vector2f(0, 0)));
    vertices.push_back(transform.transformPoint(sf::Vector2f(shape.getSize().x, 0)));
    vertices.push_back(transform.transformPoint(shape.getSize()));
    vertices.push_back(transform.transformPoint(sf::Vector2f(0, shape.getSize().y)));
    return vertices;
}

std::vector<sf::Vector2f> ColliderSquareTriangleChecker::getVertices(const sf::ConvexShape &shape) const
{
    std::vector<sf::Vector2f> vertices;
    for (size_t i = 0; i < shape.getPointCount(); ++i)
    {
        vertices.push_back(shape.getTransform().transformPoint(shape.getPoint(i)));
    }
    return vertices;
}

std::vector<sf::Vector2f> ColliderSquareTriangleChecker::getVertices(const sf::RectangleShape &shape) const
{
    std::vector<sf::Vector2f> vertices(4);
    const sf::Transform &transform = shape.getTransform();
    const sf::Vector2f &size = shape.getSize();

    vertices[0] = transform.transformPoint(0, 0);
    vertices[1] = transform.transformPoint(size.x, 0);
    vertices[2] = transform.transformPoint(size.x, size.y);
    vertices[3] = transform.transformPoint(0, size.y);

    return vertices;
}

std::vector<sf::Vector2f> ColliderSquareTriangleChecker::getSeparationAxes(const std::vector<sf::Vector2f> &vertices1, const std::vector<sf::Vector2f> &vertices2) const
{
    std::vector<sf::Vector2f> axes;

    for (size_t i = 0; i < vertices1.size(); ++i)
    {
        sf::Vector2f edge = vertices1[i] - vertices1[(i + 1) % vertices1.size()];
        axes.push_back(normalize(sf::Vector2f(-edge.y, edge.x)));
    }

    for (size_t i = 0; i < vertices2.size(); ++i)
    {
        sf::Vector2f edge = vertices2[i] - vertices2[(i + 1) % vertices2.size()];
        axes.push_back(normalize(sf::Vector2f(-edge.y, edge.x)));
    }

    return axes;
}

std::pair<float, float> ColliderSquareTriangleChecker::projectPolygon(const sf::Vector2f &axis, const std::vector<sf::Vector2f> &vertices) const
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

float ColliderSquareTriangleChecker::getOverlap(const std::pair<float, float> &projection1, const std::pair<float, float> &projection2) const
{
    // Calculer la distance entre les deux projections
    float distance = std::min(projection1.second, projection2.second) - std::max(projection1.first, projection2.first);

    // Si les projections ne se chevauchent pas (distance négative), retourner 0
    if (distance < 0)
        return 0.f;
    else
        return distance;
}

sf::Vector2f ColliderSquareTriangleChecker::getSideNormal(const sf::Vector2f &p1, const sf::Vector2f &p2) const
{
    // Calculer le vecteur du côté
    sf::Vector2f sideVector = p2 - p1;

    // Calculer la normale du côté (vecteur perpendiculaire)
    sf::Vector2f normal(-sideVector.y, sideVector.x); // Permuter les composantes et changer le signe

    // Normaliser la normale
    float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
    if (length != 0)
    {
        normal /= length;
    }

    return normal;
}

std::vector<sf::Vector2f> ColliderSquareTriangleChecker::getTriangleNormals(const std::vector<sf::Vector2f> &vertices) const
{
    std::vector<sf::Vector2f> normals;
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        // Trouver les deux sommets adjacents
        sf::Vector2f p1 = vertices[i];
        sf::Vector2f p2 = vertices[(i + 1) % vertices.size()];

        // Calculer la normale du côté et l'ajouter à la liste des normales
        normals.push_back(getSideNormal(p1, p2));
    }
    return normals;
}

std::vector<sf::Vector2f> ColliderSquareTriangleChecker::getVertices(const sf::Shape &shape) const
{
    std::vector<sf::Vector2f> vertices;
    for (unsigned int i = 0; i < shape.getPointCount(); ++i)
    {
        vertices.push_back(shape.getPoint(i));
    }
    return vertices;
}

std::vector<sf::Vector2f> ColliderSquareTriangleChecker::getTriangleSideNormals(const TriangleCollider &triangleCollider) const
{
    auto triangleVertices = getVertices(*triangleCollider.Shape);
    return getTriangleNormals(triangleVertices);
}