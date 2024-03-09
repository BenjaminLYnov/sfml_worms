#ifndef CIRCLE_H
#define CIRCLE_H

#pragma once

#include "GameObject/GameObject.h"

class CircleCollider;


class Circle : public GameObject
{
public:
    Circle();

    void Start() override;
    void Update(const float DeltaTime) override;

    std::shared_ptr<CircleCollider> CircleColliderComponent;


private:
};

#endif