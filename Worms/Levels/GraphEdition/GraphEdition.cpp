#include "GraphEdition.h"
#include <iostream>
#include "GraphEditionController.h"
#include "Cell.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "GraphData.h"

GraphEdition::GraphEdition() : Level()
{
    GD = std::make_shared<GraphData>();

    GEController = std::make_shared<GraphEditionController>();
    AddGameObject(GEController);

    // Cells
    const float Width = 50;
    const sf::Vector2f Size = sf::Vector2f(Width, Width);
    const int Lines = 2;
    const int Cols = 2;
    // const int Lines = 20;
    // const int Cols = 50;

    for (int Line = 0; Line < Lines; Line++)
    {
        for (int Col = 0; Col < Cols; Col++)
        {
            Cell *NewCell = AddCell(sf::Vector2f(Size.y * Col, Size.x * Line), Size);
            NewCell->SetName("Cell " + std::to_string(Line) + " " + std::to_string(Col));
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

void GraphEdition::SaveGraph()
{
    // for (std::shared_ptr<Cell> CurrentCell : Cells)
    // {
    //     switch (CurrentCell->CellType)
    //     {
    //     case ECellType::None:
    //         std::cout << "None\n";
    //         break;
    //     case ECellType::Square:
    //         std::cout << "Square\n";
    //         break;
    //     case ECellType::TriangleRight:
    //         std::cout << "TR\n";
    //         break;
    //     case ECellType::TriangleLeft:
    //         std::cout << "TL\n";
    //         break;
    //     }
    // }

    GD->saveGame();
}

Cell *GraphEdition::GetCellByPosition(const sf::Vector2f Position)
{
    for (std::shared_ptr<Cell> CurrentCell : Cells)
    {
        if (!CurrentCell)
            continue;
        if (!CurrentCell->Shape)
            continue;
        if (CurrentCell->Shape->getGlobalBounds().contains(Position))
        // if (CurrentCell->IsSelected(Position))
        {
            return CurrentCell.get();
        }
    }

    return nullptr;
}

// PRIVATE

Cell *GraphEdition::AddCell(const sf::Vector2f Position, const sf::Vector2f Size)
{
    std::shared_ptr<Cell> NewCell = std::make_shared<Cell>();
    NewCell->SetWorldPosition(Position);
    NewCell->SetSize(Size);
    NewCell->SetCollision(false);
    AddGameObject(NewCell);
    Cells.push_back(NewCell);
    return NewCell.get();
}
