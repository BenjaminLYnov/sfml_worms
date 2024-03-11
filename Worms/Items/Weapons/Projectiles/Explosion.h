#ifndef EXPLOSION_H
#define EXPLOSION_H

#pragma once

#include "../Weapon.h"
#include <SFML/Graphics.hpp>

class CircleCollider;
class GameObject;
class Deleguate;

class Explosion : public Weapon
{
public:
    Explosion();
    std::shared_ptr<Deleguate> DeleguateOnDestroy;

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;

    void Destroy(GameObject *GameObjectToDestroy = nullptr) override;

protected:
    virtual void OnCollisionEnter(GameObject *GameObjectHited);

    float CircleRadius = 30;
    float DammageAmount = 10.0f;

private:
    std::shared_ptr<CircleCollider> CircleColliderComponent;

    int IndexFrame = 0;

    float LifeTime = 0.7f;
    float CurrentLifeTime = 0.0f;

    void InitAnimations();
};

#endif