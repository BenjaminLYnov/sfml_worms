#ifndef CELL_H
#define CELL_H

#pragma once

#include "GameObject/GameObject.h"

// Forward declaration de sf::RectangleShape
namespace sf
{
    class RectangleShape;
}


class Cell : public GameObject
{
public:
    Cell(const sf::Vector2f Size = sf::Vector2f(10, 10));

    void Start() override;
    void Update(const float DeltaTime) override;
    void Render(sf::RenderWindow &Window) const override;

    void SetSize(const sf::Vector2f &NewSize);

private:

    std::shared_ptr<sf::RectangleShape> Shape; // Représentation graphique pour le rendu

};

#endif