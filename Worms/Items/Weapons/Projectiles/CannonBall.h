#ifndef CANNONBALL_H
#define CANNONBALL_H

#pragma once

#include "../Projectiles/IProjectile.h"
#include <SFML/System/Vector2.hpp>

class SquareCollider;
class GameObject;
class Rigidbody;
class Deleguate;

class CannonBall : public IProjectile
{
public:
    CannonBall();

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;

protected:
    virtual void OnCollisionEnter(GameObject *GameObjectHited) override;
private:
};

#endif