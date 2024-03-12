#include "GraphEditionController.h"
#include "GraphEdition.h"

#include <iostream>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

// Include les Inputs Action
#include "GameObject/Components/Input/TriggerEvent.h"
#include "./InputActions/SelectCellAction.h"
#include "./InputActions/SwitchCellTypeAction.h"
#include "./InputActions/SaveGraphAction.h"
#include "./InputActions/LoadGraphAction.h"
#include "./InputActions/LoadPartyAction.h"
#include "./InputActions/SetCellTypeToNoneAction.h"
#include "./InputActions/GraphMoveViewportAction.h"
#include "Characters/InputActions/ZoomViewportAction.h"
#include "GameObject/Components/Camera/Camera.h"
#include "GameManager/GameManager.h"

#include "Cell.h"
#include "Level/Level.h"
#include "Graph.h"

GraphEditionController::GraphEditionController() : Character()
{
    // Instance Inputs Acitons
    IaMoveViewport = std::make_shared<GraphMoveViewportAction>();
    IaZoomViewport = std::make_shared<ZoomViewportAction>();
    IaSelectCell = std::make_shared<SelectCellAction>();
    IaSwitchCellType = std::make_shared<SwitchCellTypeAction>();
    IaSaveGraph = std::make_shared<SaveGraphAction>();
    IaLoadGraph = std::make_shared<LoadGraphAction>();
    IaLoadParty = std::make_shared<LoadPartyAction>();
    IaSetCellTypeToNone = std::make_shared<SetCellTypeToNoneAction>();

    SetupBindAction();

    CameraComponent->bEnableLag = true;
    CameraComponent->SetFollowOwner(false);
    AddComponent(CameraComponent.get());
}

void GraphEditionController::Start()
{
    Character::Start();
    CameraComponent->SetWindow(GetWorld()->GetWindow());
}

void GraphEditionController::Update(const float DeltaTime)
{
    Character::Update(DeltaTime);
}

void GraphEditionController::Render(sf::RenderWindow &Window) const
{
    GameObject::Render(Window);
}

void GraphEditionController::SetGraphEditionLevel(GraphEdition *_GE)
{
    GE = _GE;
}

// PROTECTED

void GraphEditionController::SetupBindAction()
{
    InputComponent->BindAction(IaMoveViewport, ETriggerEvent::Triggered, this, &GraphEditionController::MoveViewport);
    InputComponent->BindAction(IaZoomViewport, ETriggerEvent::Triggered, this, &GraphEditionController::ZoomViewport);
    InputComponent->BindAction(IaSelectCell, ETriggerEvent::Triggered, this, &GraphEditionController::SelectCell);
    InputComponent->BindAction(IaSwitchCellType, ETriggerEvent::Started, this, &GraphEditionController::SwitchCellType);
    InputComponent->BindAction(IaSaveGraph, ETriggerEvent::Started, this, &GraphEditionController::SaveGraph);
    InputComponent->BindAction(IaLoadGraph, ETriggerEvent::Started, this, &GraphEditionController::LoadGraph);
    InputComponent->BindAction(IaLoadParty, ETriggerEvent::Started, this, &GraphEditionController::LoadParty);
    InputComponent->BindAction(IaSetCellTypeToNone, ETriggerEvent::Triggered, this, &GraphEditionController::SetCellTypeToNone);
}

void GraphEditionController::MoveViewport(const sf::Vector2f Value)
{
    CameraComponent->MoveView(Value * SpeedMoveView * GetWorld()->GetWorldDeltaSecond());
}

void GraphEditionController::ZoomViewport(const sf::Vector2f Value)
{
    CameraComponent->SetZoom(CameraComponent->GetZoom() + Value.x * SpeedZoom * GetWorld()->GetWorldDeltaSecond());
}

void GraphEditionController::SelectCell()
{
    Cell *CellHited = GetCellByMousePosition();
    if (!CellHited)
        return;

    if (CellHited->CellType == ECellType::None && CellType != ECellType::None && GE->G->GetCellUnoneCount() > GE->MaxCellUnone)
        return;

    CellHited->SetCellType(CellType);
}

void GraphEditionController::SetCellTypeToNone()
{
    Cell *CellHited = GetCellByMousePosition();
    if (!CellHited)
        return;
    CellHited->SetCellType(ECellType::None);
}

void GraphEditionController::SwitchCellType()
{
    switch (CellType)
    {
    case ECellType::None:
        CellType = ECellType::Square;
        break;
    case ECellType::Square:
        CellType = ECellType::TriangleRight;
        break;
    case ECellType::TriangleRight:
        CellType = ECellType::TriangleLeft;
        break;
    case ECellType::TriangleLeft:
        CellType = ECellType::None;
        break;
    }
}

void GraphEditionController::SaveGraph()
{
    GE->SaveGraph();
}

void GraphEditionController::LoadGraph()
{
    GE->G->LoadGraph();
}

void GraphEditionController::LoadParty()
{
    SaveGraph();
    GE->GM->LoadLevel("Party");
}

// PRIVATE

Cell *GraphEditionController::GetCellByMousePosition()
{
    sf::Vector2i MouseLocation = sf::Mouse::getPosition(*GetWorld()->GetWindow());
    sf::Vector2f WorldMouseLocation = GetWorld()->GetWindow()->mapPixelToCoords(MouseLocation);
    Cell *CellHited = GE->GetCellByPosition(WorldMouseLocation);
    return CellHited;
}
