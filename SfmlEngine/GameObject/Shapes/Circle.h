#ifndef CIRCLE_H
#define CIRCLE_H

#pragma once

#include "GameObject/GameObject.h"

class Circle : public GameObject
{
public:
    Circle();

    void Start() override;
    void Update(const float DeltaTime) override;

private:
};

#endif