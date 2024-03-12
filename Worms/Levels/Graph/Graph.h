#ifndef GRAPH_H
#define GRAPH_H

#pragma once

#include <vector>
#include <memory>
#include <SFML/System/Vector2.hpp>

class Cell;
class GraphData;
class Level;

namespace sf
{
    class Texture; // Forward declaration pour sf::Texture
}

class Graph
{
public:
    Graph();

    void Init();
    float GetCellUnoneCount() const;
    void LoadGraph();
    void EnableCellsCollision(const bool bEnable);

    std::vector<std::shared_ptr<Cell>> Cells;
    Level *World = nullptr;

    std::shared_ptr<GraphData> GD;

private:
    const float CellWidth = 100;
    // const float CellWidth = 50;
    const int Lines = 5;
    const int Cols = 10;
    // const int Lines = 20;
    // const int Cols = 50;
    std::shared_ptr<sf::Texture> TextureTileGround; // std::shared_ptr pour sf::Texture

    std::shared_ptr<Cell> AddCell(const sf::Vector2f Position = sf::Vector2f(0, 0), const sf::Vector2f Size = sf::Vector2f(10, 10));
};

#endif