#include "GraphEditionController.h"
#include "GraphEdition.h"

#include <iostream>

// Include les Inputs Action
#include "GameObject/Components/Input/TriggerEvent.h"
#include "./InputActions/SwitchTypeCellToLeft.h"
#include "./InputActions/SwitchTypeCellToRight.h"

GraphEditionController::GraphEditionController() : Character()
{
    // Instance Inputs Acitons
    IaSwitchTypeCellToLeft = std::make_shared<SwitchTypeCellToLeft>();
    IaSwitchTypeCellToRight = std::make_shared<SwitchTypeCellToRight>();
    SetupBindAction();
}

void GraphEditionController::Start()
{
    Character::Start();
}

void GraphEditionController::Update(const float DeltaTime)
{
    Character::Update(DeltaTime);
}

void GraphEditionController::SetGraphEditionLevel(GraphEdition *_GE)
{
    GE = _GE;
}

// PROTECTED
void GraphEditionController::SetupBindAction()
{
    InputComponent->BindAction(IaSwitchTypeCellToRight, ETriggerEvent::Started, this, &GraphEditionController::Test);
}

void GraphEditionController::Test()
{
    GE->Rara();
}
