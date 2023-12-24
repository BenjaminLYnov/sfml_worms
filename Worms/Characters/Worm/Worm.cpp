#include "Worm.h"
#include <iostream>
#include "GameObject/Components/Sprite/Sprite.h"
#include "Resources/Resources.h"

Worm::Worm()
{

    // Crée un std::shared_ptr pour un nouvel objet Sprite
    mSprite = std::make_shared<Sprite>(circle50_data, circle50_size);

    // Ajoute le Sprite comme composant
    AddComponent(mSprite);

    SetWorldPosition(sf::Vector2f(400, 300));
}

void Worm::Start()
{
    Actor::Start();
    // std::cout << "worm start\n";
}

void Worm::Update(const float DeltaTime)
{
    Actor::Update(DeltaTime);

    // std::cout << "worm update\n";
}

void Worm::Render(sf::RenderWindow &Window) const
{
    Actor::Render(Window);
    // std::cout << "worm render\n";
}
