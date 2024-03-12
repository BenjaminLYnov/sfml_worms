#include "SquareCollider.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject/GameObject.h"
#include <iostream>
#include "GameObject/Components/Rigidbody/Rigidbody.h"
#include "GameObject/Character/Character.h"
#include "Math/Vector/Vector.h"
#include <cmath>
#include <algorithm>
#include <array>
#include "ColliderChecker.h"
#include "HitResult.h"

SquareCollider::SquareCollider(const sf::Vector2f InitialSize) : ICollider(), Size(InitialSize)
{
    // Initialisation spécifique de SquareCollider

    Shape = std::make_shared<sf::RectangleShape>(Size);
    SetSize(Size);

    // Définit la couleur de remplissage du rectangle en transparent
    Shape->setFillColor(sf::Color::Transparent);

    // Définit l'épaisseur de la bordure du rectangle
    Shape->setOutlineThickness(1);

    // Définit une couleur pour la bordure, par exemple, verte
    Shape->setOutlineColor(sf::Color::Green);

    Rect.width = Size.x;
    Rect.height = Size.y;
}

SquareCollider::~SquareCollider()
{
}

void SquareCollider::Start()
{
    // Implémentation de la logique de démarrage spécifique à SquareCollider
    UpdatePosition();
    InitCollider();
}

void SquareCollider::Update(const float DeltaTime)
{
    // Implémentation de la logique de mise à jour spécifique à SquareCollider
    UpdatePosition();
}

void SquareCollider::Render(sf::RenderWindow &Window)
{
#ifndef NDEBUG
    if (Shape)
        Window.draw(*Shape);
#endif
}

void SquareCollider::CancelCollision(ICollider *Other)
{
    SquareCollider *OtherSquare = dynamic_cast<SquareCollider *>(Other);
    sf::Vector2f CancelVector = GetCollisionResolutionVector(*Shape, *OtherSquare->Shape);
    GetOwner()->AddWorldPosition(CancelVector);
}

HitResult SquareCollider::TestCollision(const SquareCollider &Other) const
{
    if (!Shape || !Other.Shape)
        return HitResult();

    const bool bIsOnCollision = RectangleShapeTestCollision(*Shape, *Other.Shape);
    const sf::Vector2f CancelVector = GetCollisionResolutionVector(*Shape, *Other.Shape);
    const sf::Vector2f Normal = -GetVectorNormal(*Shape, *Other.Shape);
    const float Distance = getCollisionResolutionDistance(*Shape, *Other.Shape);
    return HitResult(bIsOnCollision, Normal, Distance);
}

void SquareCollider::SetSize(const sf::Vector2f &NewSize)
{
    Size = NewSize;
    if (!Shape)
        return;
    Shape->setSize(Size);
    Shape->setOrigin(sf::Vector2f(Size.x / 2, Size.y / 2));
}

sf::Vector2f SquareCollider::GetSize() const
{
    return Size;
}

sf::FloatRect SquareCollider::GetRect() const
{
    return Rect;
}

// PROTECTED

void SquareCollider::UpdatePosition()
{
    if (!GetOwner())
        return;
    const sf::Vector2f NewPos = GetOwner()->GetWorldPosition() + GetOwner()->GetRelativePosition() + Offset;
    Shape->setPosition(NewPos);
    Rect.left = NewPos.x - Rect.width / 2;
    Rect.top = NewPos.y - Rect.height / 2;
}

void SquareCollider::CancelCollisionWith(const std::shared_ptr<SquareCollider> OtherCollider)
{
    if (!OtherCollider)
        return;

    sf::Vector2f CancelVector = GetCollisionResolutionVector(*Shape, *OtherCollider->Shape);
    GetOwner()->AddWorldPosition(CancelVector);
}

// Private

sf::Vector2f SquareCollider::getCenter(const sf::RectangleShape &shape) const
{
    return sf::Vector2f(shape.getPosition().x + shape.getSize().x / 2,
                        shape.getPosition().y + shape.getSize().y / 2);
}

sf::Vector2f SquareCollider::GetMoveAwayDirection(sf::RectangleShape &mover, const sf::RectangleShape &obstacle) const
{
    sf::FloatRect moverBounds = mover.getGlobalBounds();
    sf::FloatRect obstacleBounds = obstacle.getGlobalBounds();

    // Calculer le vecteur de translation minimal en x et y pour séparer les boîtes englobantes
    float deltaX = (moverBounds.left + moverBounds.width / 2) - (obstacleBounds.left + obstacleBounds.width / 2);
    float deltaY = (moverBounds.top + moverBounds.height / 2) - (obstacleBounds.top + obstacleBounds.height / 2);

    // Calculer la profondeur de la pénétration en x et y
    float intersectX = std::min(moverBounds.left + moverBounds.width, obstacleBounds.left + obstacleBounds.width) - std::max(moverBounds.left, obstacleBounds.left);
    float intersectY = std::min(moverBounds.top + moverBounds.height, obstacleBounds.top + obstacleBounds.height) - std::max(moverBounds.top, obstacleBounds.top);

    // Créer un vecteur de translation basé sur la direction et la profondeur de la pénétration
    sf::Vector2f translation;
    if (intersectX < intersectY)
    {
        translation.x = deltaX < 0 ? -intersectX : intersectX;
    }
    else
    {
        translation.y = deltaY < 0 ? -intersectY : intersectY;
    }

    Vector::Normalized(translation);

    return translation;
}

float SquareCollider::getCollisionResolutionDistance(const sf::RectangleShape &mover, const sf::RectangleShape &obstacle) const
{
    auto MoverCorners = GetTransformedCorners(mover);
    auto ObstacleCorners = GetTransformedCorners(obstacle);

    // Concaténation des axes normaux des deux rectangles
    std::array<sf::Vector2f, 4> Axes = {
        Normalize(MoverCorners[1] - MoverCorners[0]),
        Normalize(MoverCorners[3] - MoverCorners[0]),
        Normalize(ObstacleCorners[1] - ObstacleCorners[0]),
        Normalize(ObstacleCorners[3] - ObstacleCorners[0])};

    float MinOverlap = std::numeric_limits<float>::infinity();
    sf::Vector2f SmallestAxis;

    for (const auto &Axis : Axes)
    {
        auto MoverProj = GetProjection(MoverCorners, Axis);
        auto ObstacleProj = GetProjection(ObstacleCorners, Axis);

        float Overlap = std::min(MoverProj.second, ObstacleProj.second) - std::max(MoverProj.first, ObstacleProj.first);

        // Si il n'y a pas de chevauchement, pas de collision
        if (Overlap < 0)
        {
            return 0; // Pas de collision
        }

        // Trouver l'axe avec le plus petit chevauchement
        if (Overlap < MinOverlap)
        {
            MinOverlap = Overlap;
            SmallestAxis = Axis;
        }
    }

    return MinOverlap;
}

// Check Collision

bool SquareCollider::isPointInRotatedRect(const sf::Vector2f &point, const sf::RectangleShape &rect) const
{
    sf::Transform inverse = rect.getInverseTransform();
    sf::Vector2f localPoint = inverse.transformPoint(point);
    sf::FloatRect bounds = rect.getLocalBounds();
    return bounds.contains(localPoint);
}

bool SquareCollider::RectangleShapeTestCollision(const sf::RectangleShape &rect1, const sf::RectangleShape &rect2) const
{
    // Vérifie si les coins de rect1 sont dans rect2

    for (size_t i = 0; i < 4; ++i)
    {
        if (isPointInRotatedRect(rect1.getTransform().transformPoint(rect1.getPoint(i)), rect2))
        {
            return true;
        }
    }

    // Vérifie si les coins de rect2 sont dans rect1
    for (size_t i = 0; i < 4; ++i)
    {
        if (isPointInRotatedRect(rect2.getTransform().transformPoint(rect2.getPoint(i)), rect1))
        {
            return true;
        }
    }

    // Pas de collision détectée
    return false;
}

// Utilitaire pour calculer les axes normaux pour SAT
std::array<sf::Vector2f, 2> SquareCollider::GetRectangleAxes(const std::array<sf::Vector2f, 4> &corners)
{
    std::array<sf::Vector2f, 2> axes;
    axes[0] = corners[1] - corners[0];
    axes[1] = corners[3] - corners[0];
    // Normalisation des axes
    for (auto &axis : axes)
    {
        float length = std::sqrt(axis.x * axis.x + axis.y * axis.y);
        axis = sf::Vector2f(-axis.y / length, axis.x / length);
    }
    return axes;
}

// Utilitaire pour calculer les coins transformés d'un rectangle
std::array<sf::Vector2f, 4> SquareCollider::GetTransformedCorners(const sf::RectangleShape &rect) const
{
    std::array<sf::Vector2f, 4> corners;
    for (size_t i = 0; i < 4; ++i)
    {
        corners[i] = rect.getTransform().transformPoint(rect.getPoint(i));
    }
    return corners;
}

// Projection d'un coin sur un axe
float SquareCollider::ProjectCornerOnAxis(const sf::Vector2f &corner, const sf::Vector2f &axis) const
{
    return corner.x * axis.x + corner.y * axis.y;
}

// Calcul de l'axe normalisé
sf::Vector2f SquareCollider::Normalize(const sf::Vector2f &axis) const
{
    float length = std::sqrt(axis.x * axis.x + axis.y * axis.y);
    return axis / length;
}

// Fonction pour obtenir la projection d'un rectangle sur un axe
std::pair<float, float> SquareCollider::GetProjection(const std::array<sf::Vector2f, 4> &corners, const sf::Vector2f &axis) const
{
    float minProj = ProjectCornerOnAxis(corners[0], axis);
    float maxProj = minProj;
    for (const auto &corner : corners)
    {
        float projection = ProjectCornerOnAxis(corner, axis);
        minProj = std::min(minProj, projection);
        maxProj = std::max(maxProj, projection);
    }
    return {minProj, maxProj};
}

// Fonction pour calculer la distance nécessaire pour résoudre la collision
sf::Vector2f SquareCollider::GetCollisionResolutionVector(const sf::RectangleShape &Mover, const sf::RectangleShape &Obstacle) const
{
    auto MoverCorners = GetTransformedCorners(Mover);
    auto ObstacleCorners = GetTransformedCorners(Obstacle);

    // Concaténation des axes normaux des deux rectangles
    std::array<sf::Vector2f, 4> Axes = {
        Normalize(MoverCorners[1] - MoverCorners[0]),
        Normalize(MoverCorners[3] - MoverCorners[0]),
        Normalize(ObstacleCorners[1] - ObstacleCorners[0]),
        Normalize(ObstacleCorners[3] - ObstacleCorners[0])};

    float MinOverlap = std::numeric_limits<float>::infinity();
    sf::Vector2f SmallestAxis;

    for (const auto &Axis : Axes)
    {
        auto MoverProj = GetProjection(MoverCorners, Axis);
        auto ObstacleProj = GetProjection(ObstacleCorners, Axis);

        float Overlap = std::min(MoverProj.second, ObstacleProj.second) - std::max(MoverProj.first, ObstacleProj.first);

        // Si il n'y a pas de chevauchement, pas de collision
        if (Overlap < 0)
        {
            return sf::Vector2f(0, 0); // Pas de collision
        }

        // Trouver l'axe avec le plus petit chevauchement
        if (Overlap < MinOverlap)
        {
            MinOverlap = Overlap;
            SmallestAxis = Axis;
        }
    }

    // Trouver la direction de la force de résolution
    sf::Vector2f CenterMover(Mover.getPosition().x + Mover.getGlobalBounds().width / 2,
                             Mover.getPosition().y + Mover.getGlobalBounds().height / 2);
    sf::Vector2f CenterObstacle(Obstacle.getPosition().x + Obstacle.getGlobalBounds().width / 2,
                                Obstacle.getPosition().y + Obstacle.getGlobalBounds().height / 2);
    sf::Vector2f D = CenterMover - CenterObstacle;
    if (ProjectCornerOnAxis(D, SmallestAxis) < 0)
    {
        SmallestAxis = -SmallestAxis;
    }
    // Retourner la distance de résolution multipliée par l'axe de résolution
    sf::Vector2f ResolutionVector = SmallestAxis * MinOverlap;

    return ResolutionVector;
}

sf::Vector2f SquareCollider::GetVectorNormal(const sf::RectangleShape &Mover, const sf::RectangleShape &Obstacle) const
{
    auto MoverCorners = GetTransformedCorners(Mover);
    auto ObstacleCorners = GetTransformedCorners(Obstacle);

    // Concaténation des axes normaux des deux rectangles
    std::array<sf::Vector2f, 4> Axes = {
        Normalize(MoverCorners[1] - MoverCorners[0]),
        Normalize(MoverCorners[3] - MoverCorners[0]),
        Normalize(ObstacleCorners[1] - ObstacleCorners[0]),
        Normalize(ObstacleCorners[3] - ObstacleCorners[0])};

    float MinOverlap = std::numeric_limits<float>::infinity();
    sf::Vector2f SmallestAxis;

    for (const auto &Axis : Axes)
    {
        auto MoverProj = GetProjection(MoverCorners, Axis);
        auto ObstacleProj = GetProjection(ObstacleCorners, Axis);

        float Overlap = std::min(MoverProj.second, ObstacleProj.second) - std::max(MoverProj.first, ObstacleProj.first);

        // Si il n'y a pas de chevauchement, pas de collision
        if (Overlap < 0)
        {
            return sf::Vector2f(0, 0); // Pas de collision
        }

        // Trouver l'axe avec le plus petit chevauchement
        if (Overlap < MinOverlap)
        {
            MinOverlap = Overlap;
            SmallestAxis = Axis;
        }
    }

    // Trouver la direction de la force de résolution
    sf::Vector2f CenterMover(Mover.getPosition().x + Mover.getGlobalBounds().width / 2,
                             Mover.getPosition().y + Mover.getGlobalBounds().height / 2);
    sf::Vector2f CenterObstacle(Obstacle.getPosition().x + Obstacle.getGlobalBounds().width / 2,
                                Obstacle.getPosition().y + Obstacle.getGlobalBounds().height / 2);
    sf::Vector2f D = CenterMover - CenterObstacle;
    if (ProjectCornerOnAxis(D, SmallestAxis) < 0)
    {
        SmallestAxis = -SmallestAxis;
    }

    // if (Mover.getPosition().x < Obstacle.getPosition().x)
    //     SmallestAxis.x = -1 * SmallestAxis.x;

    return SmallestAxis;
}
