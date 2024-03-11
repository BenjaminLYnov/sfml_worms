#ifndef DEADZONE_H
#define DEADZONE_H

#pragma once
#include "GameObject/GameObject.h"

class SquareCollider;

class DeadZone : public GameObject
{
public:
    DeadZone();

    void Start() override;

private:
    std::shared_ptr<SquareCollider> SquareColliderComponent;
    void OnCollisionEnter(GameObject *GameObjectHited);
};

#endif