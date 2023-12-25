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
    Shape->setOutlineThickness(0.5f);

    // Définit une couleur pour la bordure, par exemple, verte
    Shape->setOutlineColor(sf::Color::Green);
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
    // sf::Vector2f CurrentPosition = GetRelativePosition();
    // sf::Vector2f NewPosition = GetOwner()->GetWorldPosition() + CurrentPosition;
    // SetRelativePosition(NewPosition);
    // Shape->setPosition(GetRelativePosition());
}

void SquareCollider::Update(const float DeltaTime)
{
    // Implémentation de la logique de mise à jour spécifique à SquareCollider
    Shape->setPosition(GetOwner()->GetWorldPosition() + Offset);
}

void SquareCollider::Render(sf::RenderWindow &Window)
{
    // Rendu du collider carré, si nécessaire
    if (Shape)
        Window.draw(*Shape);
}

void SquareCollider::OnCollisionEnter(ICollider *Other)
{
    // Logique de gestion de l'entrée en collision
}

void SquareCollider::OnCollisionStay(ICollider *Other)
{
    // Logique de gestion du maintien de la collision
}

void SquareCollider::OnCollisionExit(ICollider *Other)
{
    // Logique de gestion de la fin de la collision
}

void SquareCollider::SetSize(const sf::Vector2f &NewSize)
{
    Size = NewSize;
    if (!Shape)
        return;
    Shape->setSize(Size);
    Shape->setOrigin(Size.x / 2, Size.y / 2);
}

sf::Vector2f SquareCollider::GetSize() const
{
    return Size;
}
