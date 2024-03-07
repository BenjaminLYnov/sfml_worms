#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Cell::Cell(const sf::Vector2f Size) : GameObject()
{
    Shape = std::make_shared<sf::RectangleShape>();
    SetSize(Size);

     // Définit la couleur de remplissage du rectangle en transparent
    Shape->setFillColor(sf::Color::Transparent);

    // Définit l'épaisseur de la bordure du rectangle
    Shape->setOutlineThickness(0.5);

    // Définit une couleur pour la bordure, par exemple, verte
    Shape->setOutlineColor(sf::Color::White);
}

void Cell::Start()
{
    GameObject::Start();
}

void Cell::Update(const float DeltaTime)
{
    GameObject::Update(DeltaTime);

    Shape->setPosition(GetWorldPosition());
}

void Cell::Render(sf::RenderWindow &Window) const
{
    GameObject::Render(Window);

    if (Shape)
        Window.draw(*Shape);
}

void Cell::SetSize(const sf::Vector2f &NewSize)
{
    if (!Shape)
        return;
    Shape->setSize(NewSize);
    Shape->setOrigin(NewSize.x / 2, NewSize.y / 2);
}
