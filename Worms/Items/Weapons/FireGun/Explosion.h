#ifndef EXPLOSION_H
#define EXPLOSION_H

#pragma once

#include "../Weapon.h"
#include <SFML/Graphics.hpp>

class SquareCollider;
class GameObject;
class Deleguate;

class Explosion : public Weapon
{
public:
    Explosion();

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;

protected:
    virtual void OnCollisionStay(GameObject *GameObjectHited);

private:
    std::shared_ptr<SquareCollider> SquareColliderComponent;

    void InitAnimations();
};

#endif