#ifndef FIREGUN_H
#define FIREGUN_H

#pragma once

#include "../Weapon.h"
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour sf::Vector2f en raison de sa nature en tant que type de template spécialisé

class SquareCollider;
class GameObject;
class Rigidbody;
class Deleguate;

class FireGun : public Weapon
{
public:
    FireGun();

    std::shared_ptr<Deleguate> DeleguateOnDestroy;

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;

    virtual void AddForce(const sf::Vector2f &Force);

protected:
    virtual void OnCollisionEnter(GameObject *GameObjectHited);

private:
    std::shared_ptr<SquareCollider> SquareColliderComponent;
    std::shared_ptr<Rigidbody> RigidbodyComponent;

    float LifeTime = 10.0f;

};

#endif