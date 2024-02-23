#ifndef ITEM_H
#define ITEM_H

#pragma once

#include "GameObject/GameObject.h"

class SquareCollider;
class Sprite;

class Item : public GameObject
{
public:
    Item();
    virtual ~Item() = default;

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;

    virtual GameObject* GetOwner();
    virtual void SetOwner(GameObject* _Owner);
    
protected:
    std::shared_ptr<Sprite> Animation;
    std::shared_ptr<Sprite> Icon;

private:
    GameObject* Owner;

};

#endif