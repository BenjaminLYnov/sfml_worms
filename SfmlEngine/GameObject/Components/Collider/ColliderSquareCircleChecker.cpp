#include "ColliderSquareCircleChecker.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>
#include "Math/Vector/Vector.h"
#include <iostream>

ColliderSquareCircleChecker::ColliderSquareCircleChecker()
{
}

HitResult ColliderSquareCircleChecker::TestCollision(const sf::RectangleShape &rectangle, const sf::CircleShape &circle) const
{
    std::vector<sf::Vector2f> rectCorners = getRotatedRectangleCorners(rectangle);
    sf::Vector2f circleCenter = circle.getPosition();
    float circleRadius = circle.getRadius();

    sf::Vector2f correctionVector(0.0f, 0.0f);

    float minDistance = std::numeric_limits<float>::max();
    bool bIsOnCollision = false;
    sf::Vector2f Normal;


    // Vérifier la distance du centre du cercle à chaque arête du rectangle
    for (size_t i = 0; i < rectCorners.size(); ++i)
    {
        sf::Vector2f start = rectCorners[i];
        sf::Vector2f end = rectCorners[(i + 1) % rectCorners.size()];
        sf::Vector2f closestPoint = closestPointOnSegment(start, end, circleCenter);
        float distance = std::hypot(circleCenter.x - closestPoint.x, circleCenter.y - closestPoint.y);

        if (distance < minDistance)
        {
            minDistance = distance;
            sf::Vector2f direction = circleCenter - closestPoint;
            Normal = direction;
            float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (magnitude > 0)
            {
                direction /= magnitude; // Normalize the direction
            }
            correctionVector = direction * (circleRadius - distance);
        }
    }

    // Si minDistance est supérieur au rayon, il n'y a pas de collision
    if (minDistance > circleRadius)
    {
        return HitResult();
    }

    return HitResult(true);
    // return HitResult(true, Normal, minDistance);
}

// PRIVATE

sf::Vector2f ColliderSquareCircleChecker::getNormalBetweenSquareAndCircle(const sf::RectangleShape &rectangle, const sf::CircleShape &circle) const
{
    sf::Vector2f circleCenter = circle.getPosition();
    sf::Vector2f closestPoint = getClosestPointOnRectangle(rectangle, circleCenter);
    sf::Vector2f sideVector;

    // Trouver le côté du rectangle le plus proche du cercle
    if (closestPoint.x == rectangle.getPosition().x) // Côté gauche du rectangle
        sideVector = sf::Vector2f(-1.f, 0.f);
    else if (closestPoint.x == rectangle.getPosition().x + rectangle.getSize().x) // Côté droit du rectangle
        sideVector = sf::Vector2f(1.f, 0.f);
    else if (closestPoint.y == rectangle.getPosition().y) // Côté supérieur du rectangle
        sideVector = sf::Vector2f(0.f, -1.f);
    else // Côté inférieur du rectangle
        sideVector = sf::Vector2f(0.f, 1.f);

    // Calculer la normale
    sf::Vector2f normal(-sideVector.y, sideVector.x); // Permuter les composantes et changer le signe

    return normal;
}

// Fonction pour calculer le vecteur de correction pour séparer le cercle et le rectangle rotatif
sf::Vector2f ColliderSquareCircleChecker::calculateCorrectionVector(const sf::RectangleShape &rectangle, const sf::CircleShape &circle) const
{
    std::vector<sf::Vector2f> rectCorners = getRotatedRectangleCorners(rectangle);
    sf::Vector2f circleCenter = circle.getPosition();
    float circleRadius = circle.getRadius();

    sf::Vector2f correctionVector(0.0f, 0.0f);
    float minDistance = std::numeric_limits<float>::max();

    // Vérifier la distance du centre du cercle à chaque arête du rectangle
    for (size_t i = 0; i < rectCorners.size(); ++i)
    {
        sf::Vector2f start = rectCorners[i];
        sf::Vector2f end = rectCorners[(i + 1) % rectCorners.size()];
        sf::Vector2f closestPoint = closestPointOnSegment(start, end, circleCenter);
        float distance = std::hypot(circleCenter.x - closestPoint.x, circleCenter.y - closestPoint.y);

        if (distance < minDistance)
        {
            minDistance = distance;
            sf::Vector2f direction = circleCenter - closestPoint;
            float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (magnitude > 0)
            {
                direction /= magnitude; // Normalize the direction
            }
            correctionVector = direction * (circleRadius - distance);
        }
    }

    // Si minDistance est supérieur au rayon, il n'y a pas de collision
    if (minDistance > circleRadius)
    {
        return sf::Vector2f(0, 0); // Pas de correction nécessaire
    }

    return correctionVector;
}

// Fonction pour calculer le point le plus proche sur un segment de ligne à un point donné
sf::Vector2f ColliderSquareCircleChecker::closestPointOnSegment(sf::Vector2f segmentStart, sf::Vector2f segmentEnd, sf::Vector2f point) const
{
    sf::Vector2f segmentDirection = segmentEnd - segmentStart;
    float segmentLengthSquared = segmentDirection.x * segmentDirection.x + segmentDirection.y * segmentDirection.y;
    if (segmentLengthSquared == 0.0f)
        return segmentStart; // Le segment est un point

    float t = ((point.x - segmentStart.x) * segmentDirection.x + (point.y - segmentStart.y) * segmentDirection.y) / segmentLengthSquared;
    t = std::max(0.0f, std::min(1.0f, t)); // Clamp t entre 0 et 1

    return segmentStart + t * segmentDirection; // Calculer et retourner le point le plus proche
}

// Fonction pour calculer la distance entre deux points
float ColliderSquareCircleChecker::distance(sf::Vector2f point1, sf::Vector2f point2) const
{
    return std::sqrt(std::pow(point2.x - point1.x, 2) + std::pow(point2.y - point1.y, 2));
}

// Fonction pour calculer la rotation d'un point autour d'un autre
sf::Vector2f ColliderSquareCircleChecker::rotatePoint(sf::Vector2f point, sf::Vector2f pivot, float angle) const
{
    float s = sin(angle * (3.14159265 / 180.0));
    float c = cos(angle * (3.14159265 / 180.0));

    // translate point back to origin:
    point -= pivot;

    // rotate point
    float xnew = point.x * c - point.y * s;
    float ynew = point.x * s + point.y * c;

    // translate point back:
    return sf::Vector2f(xnew + pivot.x, ynew + pivot.y);
}

// Fonction pour calculer les points du rectangle après rotation
std::vector<sf::Vector2f> ColliderSquareCircleChecker::getRotatedRectanglePoints(const sf::RectangleShape &rectangle) const
{
    sf::Vector2f center = rectangle.getPosition();
    std::vector<sf::Vector2f> points(4);
    points[0] = sf::Vector2f(-rectangle.getSize().x / 2, -rectangle.getSize().y / 2); // Haut gauche
    points[1] = sf::Vector2f(rectangle.getSize().x / 2, -rectangle.getSize().y / 2);  // Haut droit
    points[2] = sf::Vector2f(rectangle.getSize().x / 2, rectangle.getSize().y / 2);   // Bas droit
    points[3] = sf::Vector2f(-rectangle.getSize().x / 2, rectangle.getSize().y / 2);  // Bas gauche

    for (auto &point : points)
    {
        point = rotatePoint(point, sf::Vector2f(0, 0), rectangle.getRotation()) + center;
    }

    return points;
}

// Calcul de la distance d'un point à un segment (ligne)
float ColliderSquareCircleChecker::pointLineDistance(sf::Vector2f point, sf::Vector2f lineStart, sf::Vector2f lineEnd) const
{
    float lineLength = std::hypot(lineEnd.x - lineStart.x, lineEnd.y - lineStart.y);
    if (lineLength == 0.0f)
        return std::hypot(point.x - lineStart.x, point.y - lineStart.y);
    float t = ((point.x - lineStart.x) * (lineEnd.x - lineStart.x) + (point.y - lineStart.y) * (lineEnd.y - lineStart.y)) / (lineLength * lineLength);
    t = std::max(0.0f, std::min(1.0f, t));
    sf::Vector2f projection = lineStart + t * (lineEnd - lineStart);
    return std::hypot(point.x - projection.x, point.y - projection.y);
}

// Fonction pour obtenir les coins du rectangle en prenant en compte la rotation
std::vector<sf::Vector2f> ColliderSquareCircleChecker::getRotatedRectangleCorners(const sf::RectangleShape &rectangle) const
{
    sf::Vector2f rectCenter = rectangle.getPosition();
    sf::Vector2f rectSize = rectangle.getSize();
    const double PI = 3.14159265358979323846;

    float rotation = rectangle.getRotation() * (PI / 180.0f); // Convertir en radians

    std::vector<sf::Vector2f> corners(4);
    sf::Transform transform;
    transform.rotate(rectangle.getRotation(), rectCenter);

    corners[0] = transform.transformPoint(rectCenter + sf::Vector2f(-rectSize.x / 2, -rectSize.y / 2));
    corners[1] = transform.transformPoint(rectCenter + sf::Vector2f(rectSize.x / 2, -rectSize.y / 2));
    corners[2] = transform.transformPoint(rectCenter + sf::Vector2f(rectSize.x / 2, rectSize.y / 2));
    corners[3] = transform.transformPoint(rectCenter + sf::Vector2f(-rectSize.x / 2, rectSize.y / 2));

    return corners;
}

sf::Vector2f ColliderSquareCircleChecker::getClosestPointOnRectangle(const sf::RectangleShape &rectangle, const sf::Vector2f &circleCenter) const
{
    sf::FloatRect rectBounds = rectangle.getGlobalBounds();
    sf::Vector2f closestPoint;

    if (circleCenter.x < rectBounds.left) // Cercle est à gauche du rectangle
        closestPoint.x = rectBounds.left;
    else if (circleCenter.x > rectBounds.left + rectBounds.width) // Cercle est à droite du rectangle
        closestPoint.x = rectBounds.left + rectBounds.width;
    else
        closestPoint.x = circleCenter.x; // Cercle est sur le même axe horizontal que le rectangle

    if (circleCenter.y < rectBounds.top) // Cercle est au-dessus du rectangle
        closestPoint.y = rectBounds.top;
    else if (circleCenter.y > rectBounds.top + rectBounds.height) // Cercle est en dessous du rectangle
        closestPoint.y = rectBounds.top + rectBounds.height;
    else
        closestPoint.y = circleCenter.y; // Cercle est sur le même axe vertical que le rectangle

    return closestPoint;
}
