#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once
#include "GameObject/GameObject.h"

class TriangleCollider;

class Triangle : public GameObject
{
public:
    Triangle();

    void Start() override;
    void Update(const float DeltaTime) override;
    void Render(sf::RenderWindow &Window) const override;

    std::shared_ptr<TriangleCollider> TriangleColliderComponent;

private:
};

#endif