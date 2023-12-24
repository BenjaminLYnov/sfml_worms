#pragma once

#include "GameObject/Actor/Actor.h"

class Sprite;

class Worm : public Actor
{
public:
    Worm();

    void Start() override;

    void Update(const float DeltaTime);

    void Render(sf::RenderWindow &Window) const;

private:
    std::shared_ptr<Sprite> mSprite;
};
