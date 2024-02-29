#ifndef SQUARE_H
#define SQUARE_H

#pragma once

#include "GameObject/GameObject.h"

class SquareCollider;

class Square : public GameObject
{
public:
    Square();

    void Start() override;
    void Update(const float DeltaTime) override;
    void Render(sf::RenderWindow &Window) const override;

    std::shared_ptr<SquareCollider> SquareColliderComponent;

private:
};

#endif