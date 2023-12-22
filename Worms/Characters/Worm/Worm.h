#pragma once

#include "GameObject/GameObject.h"

class Worm : public GameObject
{
public:
    Worm();

    void Start() override;

    void Update(const float DeltaTime);

    void Render(sf::RenderWindow &Window) const;

private:
};
