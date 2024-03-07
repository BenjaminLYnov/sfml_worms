#ifndef GRAPHEDITIONCONTROLLER_H
#define GRAPHEDITIONCONTROLLER_H

#pragma once

#include "GameObject/Character/Character.h"

class GraphEdition;

class GraphEditionController : public Character
{
public:
    GraphEditionController();

    void Start() override;
    void Update(const float DeltaTime) override;

    void SetGraphEditionLevel(GraphEdition* _GE);

protected:
    void SetupBindAction() override;

private:
    std::shared_ptr<InputAction> IaSwitchTypeCellToLeft;
    std::shared_ptr<InputAction> IaSwitchTypeCellToRight;

    GraphEdition* GE;

    void Test();
};

#endif