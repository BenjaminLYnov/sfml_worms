#include "GraphEdition.h"
#include <iostream>
#include "GraphEditionController.h"
#include "Cell.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "Graph.h"
#include "GraphData.h"
#include "GameManager/GameManager.h"

GraphEdition::GraphEdition() : Level()
{
    G = std::make_shared<Graph>();
    GD = std::make_shared<GraphData>();

    GEController = std::make_shared<GraphEditionController>();
}

void GraphEdition::Start()
{
	GameObjects.clear();

    AddGameObject(GEController);

    SetCharacterControlled(GEController);
    GEController->SetGraphEditionLevel(this);

    G->World = this;
    G->Init();

    Level::Start();
}

void GraphEdition::Update(const float DeltaTime)
{
    Level::Update(DeltaTime);
}

void GraphEdition::SaveGraph()
{
    // Créer tableau de ECellType
    std::vector<ECellType> CellTypes;
    for (std::shared_ptr<Cell> CurrentCell : G->Cells)
        CellTypes.push_back(CurrentCell->CellType);

    GD->CellTypes = CellTypes;
    GD->SaveGraph();
}

Cell *GraphEdition::GetCellByPosition(const sf::Vector2f Position)
{
    for (std::shared_ptr<Cell> CurrentCell : G->Cells)
    {
        if (!CurrentCell)
            continue;
        if (!CurrentCell->Shape)
            continue;
        if (CurrentCell->Shape->getGlobalBounds().contains(Position))
        {
            return CurrentCell.get();
        }
    }
    return nullptr;
}

// PRIVATE
