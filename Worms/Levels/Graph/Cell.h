#ifndef CELL_H
#define CELL_H

#pragma once

#include "GameObject/GameObject.h"
#include "CellType.h"

// Forward declaration de sf::RectangleShape
namespace sf
{
    class RectangleShape;
}

class SquareCollider;
class TriangleCollider;
class GameObject;

class Cell : public GameObject
{
public:
    Cell(const sf::Vector2f Size = sf::Vector2f(10, 10));

    void Start() override;
    void Update(const float DeltaTime) override;
    void Render(sf::RenderWindow &Window) const override;

    void SetSize(const sf::Vector2f &NewSize);

    bool IsSelected(const sf::Vector2f Position) const;

    void SetCellType(const ECellType NewCellType);

    void SetCollision(const bool bCollision);

    std::shared_ptr<sf::RectangleShape> Shape; // Représentation graphique pour le rendu

    ECellType CellType = ECellType::None;

protected:
    void OnCollisionEnter(GameObject *GameObjectHited);

private:
    std::shared_ptr<SquareCollider> SquareColliderComponent;
    std::shared_ptr<TriangleCollider> TriangleLeftColliderComponent;
    std::shared_ptr<TriangleCollider> TriangleRightColliderComponent;
};

#endif