#ifndef FRAGMENTATIONBALL_H
#define FRAGMENTATIONBALL_H

#pragma once

#include "../Projectiles/IProjectile.h"
#include <SFML/System/Vector2.hpp>

class FragmentationBall : public IProjectile
{
public:
    FragmentationBall();
    std::shared_ptr<Deleguate> DeleguateOnDestroy;

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;

    virtual void AddForce(const sf::Vector2f &Force);

    void Destroy(GameObject *GameObjectToDestroy = nullptr) override;

protected:
    virtual void OnCollisionEnter(GameObject *GameObjectHited);

private:
    std::shared_ptr<SquareCollider> SquareColliderComponent;
    std::shared_ptr<Rigidbody> RigidbodyComponent;
};

#endif