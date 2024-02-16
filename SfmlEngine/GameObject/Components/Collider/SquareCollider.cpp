#include "SquareCollider.h"
#include <SFML/Graphics/RectangleShape.hpp> // Assurez-vous d'inclure la bonne bibliothèque pour les formes SFML
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject/GameObject.h"
#include <iostream>

SquareCollider::SquareCollider(const sf::Vector2f InitialSize) : Size(InitialSize)
{
    // Initialisation spécifique de SquareCollider

    Shape = new sf::RectangleShape(Size);

    Shape->setOrigin(Size.x / 2, Size.y / 2);

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
    // Nettoyage spécifique, si nécessaire
    if (Shape)
    {
        delete Shape;
        Shape = nullptr;
    }
}

void SquareCollider::Start()
{
    // Implémentation de la logique de démarrage spécifique à SquareCollider
    UpdatePosition();
}

void SquareCollider::Update(const float DeltaTime)
{
    // Implémentation de la logique de mise à jour spécifique à SquareCollider
    UpdatePosition();
}

void SquareCollider::Render(sf::RenderWindow &Window)
{
    // Rendu du collider carré, si nécessaire
    if (Shape)
        Window.draw(*Shape);
}



bool SquareCollider::IsOnCollision(std::shared_ptr<ICollider> Other)
{
    if (!Other)
        return false;

    // Vérifier si l'autre Collider est un Square Collider
    std::shared_ptr<SquareCollider> OtherCollider = std::dynamic_pointer_cast<SquareCollider>(Other);

    if (!OtherCollider)
        return false;

    // Récupérer le FloatRect de l'autre Square Collider
    const sf::FloatRect OtherRect = OtherCollider->GetRect();

    // Vérifier s'il y a collision avec l'autre
    const bool bIsOnCollision = Rect.intersects(OtherRect);

    return bIsOnCollision;
}

void SquareCollider::SetSize(const sf::Vector2f &NewSize)
{
    Size = NewSize;
    if (!Shape)
        return;
    Shape->setSize(Size);
    Shape->setOrigin(Size.x / 2, Size.y / 2);
    Rect.width = Size.x;
    Rect.height = Size.y;
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
    const sf::Vector2f NewPos = GetOwner()->GetWorldPosition() + GetOwner()->GetRelativePosition() + Offset;
    Shape->setPosition(NewPos);
    Rect.left = NewPos.x - Rect.width / 2;
    Rect.top = NewPos.y - Rect.height / 2;
}

void SquareCollider::CancelCollisionWith(const std::shared_ptr<SquareCollider> OtherCollider)
{
    if (!OtherCollider)
        return;

    sf::FloatRect Intersect;
    GetRect().intersects(OtherCollider->GetRect(), Intersect);

    sf::Vector2f CancelVector = GetVectorMoveToCancelCollision(OtherCollider->GetRect());
    // CancelVector.x *= Intersect.width;
    // CancelVector.y *= Intersect.height;
    CancelVector.x *= Intersect.width + 1;
    CancelVector.y *= Intersect.height + 1;

    GetOwner()->AddWorldPosition(CancelVector);
}

// Private

sf::Vector2f SquareCollider::GetVectorMoveToCancelCollision(sf::FloatRect OtherRect)
{
    // Get depth distance

    // Left
    float depthDistanceLeft = fabs(Rect.left + (Rect.width - OtherRect.left));

    // Right
    float depthDistanceRight = fabs(Rect.left - (OtherRect.left + OtherRect.width));

    // Up
    float depthDistanceUp = fabs((Rect.top + Rect.height) - OtherRect.top);

    // Down
    float depthDistanceDown = fabs(Rect.top - (OtherRect.top + OtherRect.height));

    // Search the less
    float minDepthDistance = depthDistanceUp;
    sf::Vector2f normalVector = sf::Vector2f(0, -1);

    if (minDepthDistance >= depthDistanceDown)
    {
        minDepthDistance = depthDistanceDown;
        normalVector = sf::Vector2f(0, 1);
    }

    if (minDepthDistance >= depthDistanceLeft)
    {
        minDepthDistance = depthDistanceLeft;
        normalVector = sf::Vector2f(-1, 0);
    }

    if (minDepthDistance >= depthDistanceRight)
    {
        minDepthDistance = depthDistanceRight;
        normalVector = sf::Vector2f(1, 0);
    }

    return normalVector;
}
