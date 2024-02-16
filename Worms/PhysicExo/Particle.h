#ifndef PARTICLE_H
#define PARTICLE_H

#pragma once

#include "GameObject/GameObject.h"

class SquareCollider;
class Rigidbody;

class Particle : public GameObject
{
public:
    Particle();
    ~Particle();

    
    void Start() override;

    void Update(const float DeltaTime) override;

    void Render(sf::RenderWindow &Window) const override;
   
    std::shared_ptr<SquareCollider> SquareColliderComponent;
    std::shared_ptr<Rigidbody> RigidbodyComponent;

private:

};

#endif