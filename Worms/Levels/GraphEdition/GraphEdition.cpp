#include "GraphEdition.h"
#include <iostream>
#include "GraphEditionController.h"
#include "Cell.h"

GraphEdition::GraphEdition() : Level()
{
    GEController = std::make_shared<GraphEditionController>();
    AddGameObject(GEController);

    // Cell

    const int Width = 100;
    const int Height = 100;

    const sf::Vector2f Size = sf::Vector2f(10, 10);

    for (int Col = 0; Col <= Width; Col++)
    {
        for (int Line = 0; Line < Width; Line++)
        {
            AddCell(sf::Vector2f(Size.x * Line, Size.y * Col), Size);
        }
    }
}

void GraphEdition::Start()
{
    Level::Start();
    SetCharacterControlled(GEController);
    GEController->SetGraphEditionLevel(this);
}

void GraphEdition::Update(const float DeltaTime)
{
    Level::Update(DeltaTime);
}

void GraphEdition::Rara()
{
    std::cout << "rara\n";
}

// PRIVATE

void GraphEdition::AddCell(const sf::Vector2f Position, const sf::Vector2f Size)
{
    std::shared_ptr<Cell> NewCell = std::make_shared<Cell>();
    NewCell->SetWorldPosition(Position);
    NewCell->SetSize(Size);
    AddGameObject(NewCell);
}
