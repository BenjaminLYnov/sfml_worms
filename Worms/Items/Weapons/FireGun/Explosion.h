#ifndef EXPLOSION_H
#define EXPLOSION_H

#pragma once

#include "../Weapon.h"
#include <SFML/Graphics.hpp>

class CircleCollider;
class GameObject;
class Deleguate;
class ExplosionAnimation;

class Explosion : public Weapon
{
public:
    Explosion();

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;

protected:
    virtual void OnCollisionEnter(GameObject *GameObjectHited);

    float CircleRadius = 50;
    float DammageAmount = 10.0f;
    float ExplosionSpriteScale = 0.6;
    float ProjectionForce = 100000;

private:
    std::shared_ptr<CircleCollider> CircleColliderComponent;
    std::shared_ptr<ExplosionAnimation> ExplosionA;

    int IndexFrame = 0;

    void InitAnimations();
};

#endif