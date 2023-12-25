#pragma once

#include "../GameObject.h"

class SquareCollider;
class ActorComponent;

class Actor : public GameObject
{
public:
    Actor();

protected:
    std::shared_ptr<SquareCollider> SquareColliderComponent;
    std::vector<std::shared_ptr<ActorComponent>> ActorComponents;
    
};
