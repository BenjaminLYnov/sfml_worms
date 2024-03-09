#ifndef GRAPHEDITIONCONTROLLER_H
#define GRAPHEDITIONCONTROLLER_H

#pragma once

#include "GameObject/Character/Character.h"
#include "CellType.h"

class GraphEdition;

class GraphEditionController : public Character
{
public:
    GraphEditionController();

    void Start() override;
    void Update(const float DeltaTime) override;
    void Render(sf::RenderWindow &Window) const override;

    void SetGraphEditionLevel(GraphEdition* _GE);

    float SpeedMoveView = 500;
    float SpeedZoom = 0.5;

protected:
    void SetupBindAction() override;

    virtual void MoveViewport(const sf::Vector2f Value);
    virtual void ZoomViewport(const sf::Vector2f Value);
    virtual void SelectCell();
    virtual void SwitchCellType();
    virtual void SaveGraph();

private:
    std::shared_ptr<InputAction> IaMoveViewport;
    std::shared_ptr<InputAction> IaZoomViewport;
    std::shared_ptr<InputAction> IaSelectCell;
    std::shared_ptr<InputAction> IaSwitchCellType;
    std::shared_ptr<InputAction> IaSaveGraph;

    ECellType CellType = ECellType::Square;

    GraphEdition* GE;


    
};

#endif