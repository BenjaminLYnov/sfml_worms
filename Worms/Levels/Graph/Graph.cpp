#include "Graph.h"
#include "Cell.h"
#include "GraphData.h"
#include "Level/Level.h"
#include <iostream>
#include "GameObject/Components/Sprite/Sprite.h"
#include "Resources/Resources.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

Graph::Graph()
{
    GD = std::make_shared<GraphData>();

    TextureTileGround = std::make_shared<sf::Texture>();
    TextureTileGround->loadFromMemory(tile_ground_data, tile_ground_size);
}

void Graph::Init()
{
    if (!World)
        return;

    Cells.clear();

    const sf::Vector2f Size = sf::Vector2f(CellWidth, CellWidth);

    for (int Line = 0; Line < Lines; Line++)
    {
        for (int Col = 0; Col < Cols; Col++)
        {
            std::shared_ptr<Cell> NewCell = AddCell(sf::Vector2f(Size.y * Col, Size.x * Line), Size);
            if (NewCell)
            {
                NewCell->SetName("Cell " + std::to_string(Line) + " " + std::to_string(Col));
                NewCell->AnimationComponent->SetTexture(TextureTileGround);
                NewCell->SetCellType(ECellType::None);
            }
        }
    }
    LoadGraph();
}

void Graph::EnableCellsCollision(const bool bEnable)
{
    for (std::shared_ptr<Cell> CurrentCell : Cells)
    {
        if (!CurrentCell)
            continue;
        CurrentCell->SetCollision(bEnable);
    }
}

// PRIVATE

std::shared_ptr<Cell> Graph::AddCell(const sf::Vector2f Position, const sf::Vector2f Size)
{
    if (!World)
        return std::shared_ptr<Cell>();

    std::shared_ptr<Cell> NewCell = std::make_shared<Cell>();
    NewCell->SetWorldPosition(Position);
    NewCell->SetSize(Size);
    NewCell->SetCollision(false);
    World->AddGameObject(NewCell);
    Cells.push_back(NewCell);
    return NewCell;
}

float Graph::GetCellUnoneCount() const
{
    float CurrentCount = 0;

    for (std::shared_ptr<Cell> CurrentCell : Cells)
    {
        if (!CurrentCell)
            continue;
        if (CurrentCell->CellType != ECellType::None)
            CurrentCount++;
    }
    return CurrentCount;
}

void Graph::LoadGraph()
{
    GD->LoadGraph();

    if (GD->CellTypes.size() == 0)
        return;

    int CurrentIndex = 0;

    for (std::shared_ptr<Cell> CurrentCell : Cells)
    {
        CurrentCell->SetCellType(GD->CellTypes[CurrentIndex]);
        if (CurrentIndex == GD->CellTypes.size() - 1)
            break;
        else
            CurrentIndex++;
    }
}
