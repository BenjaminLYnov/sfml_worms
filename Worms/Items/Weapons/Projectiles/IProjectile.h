#ifndef IPROJECTILE_H
#define IPROJECTILE_H

#pragma once

#include "../Weapon.h"
#include <SFML/System/Vector2.hpp>

class SquareCollider;
class GameObject;
class Rigidbody;
class Deleguate;
class FireGunAnimation;

class IProjectile : public Weapon
{
public:
    IProjectile();

    std::shared_ptr<Deleguate> DeleguateOnDestroy;

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;

    virtual void AddForce(const sf::Vector2f &Force);

    void Destroy(GameObject *GameObjectToDestroy = nullptr) override;

protected:
    float LifeTime = 4.0f;
    float DammageAmount;

    float FireGunSpriteScale = 0.4f;
    std::shared_ptr<FireGunAnimation> FireGunA;
    
    virtual void OnCollisionEnter(GameObject *GameObjectHited);

    std::shared_ptr<SquareCollider> SquareColliderComponent;
    std::shared_ptr<Rigidbody> RigidbodyComponent;
private:
};

#endif