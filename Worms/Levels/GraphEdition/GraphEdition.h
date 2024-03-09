#ifndef GRAPHEDITION_H
#define GRAPHEDITION_H

#pragma once
#include "Level/Level.h"

class GraphEditionController;
class Cell;
class GraphData;

class GraphEdition : public Level
{
public:
    GraphEdition();

    void Start() override;
    void Update(const float DeltaTime) override;

    void Rara();

    Cell *GetCellByPosition(const sf::Vector2f Position);
    
    void SaveGraph();
    
    std::vector<std::shared_ptr<Cell>> Cells;
protected:
private:
    std::shared_ptr<GraphEditionController> GEController;

    Cell* AddCell(const sf::Vector2f Position = sf::Vector2f(0, 0), const sf::Vector2f Size = sf::Vector2f(10, 10));

    std::shared_ptr<GraphData> GD;

};

#endif