#include "Worm.h"
#include <iostream>
#include "GameObject/Components/Sprite/Sprite.h"

Worm::Worm()
{
    // AddComponent(std::make_shared<Sprite>("IMG_20231117_204520.jpg"));
    AddComponent(std::make_shared<Sprite>("./resources/LongRoyalSword.PNG"));
}

void Worm::Start()
{
    // std::cout << "worm start\n";
}

void Worm::Update(const float DeltaTime)
{
    // std::cout << "worm update\n";
}

void Worm::Render(sf::RenderWindow &Window) const
{
    GameObject::Render(Window);
    // std::cout << "worm render\n";
}
