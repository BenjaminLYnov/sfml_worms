#pragma once

#include "./../IComponent.h"
#include "Mode.h"

class StateMode : public IComponent
{
public:
    StateMode(EMode InitialMode = EMode::IDLE);

    virtual void Start() override;

    virtual void Update(const float DeltaTime) override;

protected:
    EMode Mode;
};
