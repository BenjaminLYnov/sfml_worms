#ifndef EXPLOSION_H
#define EXPLOSION_H

#pragma once

#include "../Weapon.h"
#include <SFML/Graphics.hpp>

class CircleCollider;
class GameObject;
class Deleguate;
class ExplosionAnimation;
class Sound;

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

    float CircleRadius = 50;
    float DammageAmount = 10.0f;
    float ExplosionSpriteScale = 0.6;
    float ProjectionForce = 30000;

private:
    std::shared_ptr<CircleCollider> CircleColliderComponent;
    std::shared_ptr<ExplosionAnimation> ExplosionA;
    std::shared_ptr<Sound> SoundExplosion;
    int IndexFrame = 0;
};

#endif