#ifndef GRAPHEDITION_H
#define GRAPHEDITION_H

#pragma once
#include "Level/Level.h"

class GraphEditionController;
class Cell;

class GraphEdition : public Level
{
public:
    GraphEdition();

    void Start() override;
    void Update(const float DeltaTime) override;

    void Rara();

protected:
private:
    std::shared_ptr<GraphEditionController> GEController;
    std::vector<Cell*> Cells;

    void AddCell(const sf::Vector2f Position = sf::Vector2f(0, 0), const sf::Vector2f Size = sf::Vector2f(10, 10));
};

#endif