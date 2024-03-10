#ifndef GRAPHEDITION_H
#define GRAPHEDITION_H

#pragma once
#include "Level/Level.h"

class GraphEditionController;
class Cell;
class GraphData;
class Graph;

class GraphEdition : public Level
{
public:
    GraphEdition();

    void Start() override;
    void Update(const float DeltaTime) override;


    Cell *GetCellByPosition(const sf::Vector2f Position);
    
    void SaveGraph();

    const float MaxCellUnone = 400;
    std::shared_ptr<Graph> G;
    
protected:
private:
    std::shared_ptr<GraphEditionController> GEController;
    std::shared_ptr<GraphData> GD;
    

};

#endif