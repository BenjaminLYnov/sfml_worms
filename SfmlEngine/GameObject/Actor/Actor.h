#pragma once

#include "../GameObject.h"

class SquareCollider;

class Actor : public GameObject
{
public:
    Actor();

protected:
    std::shared_ptr<SquareCollider> SquareColliderComponent;

};
