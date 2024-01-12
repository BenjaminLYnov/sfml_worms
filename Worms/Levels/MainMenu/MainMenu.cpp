#include "MainMenu.h"
#include <iostream>
#include "Characters/Worm/Worm.h"

MainMenu::MainMenu()
{
    // Instance Main Character 
    std::shared_ptr<Worm> MainWorm = std::make_shared<Worm>();

    std::shared_ptr<Worm> AnotherWorm = std::make_shared<Worm>();
    AnotherWorm->SetWorldPosition(sf::Vector2f(200, 200));


    AddGameObject(MainWorm);
    AddGameObject(AnotherWorm);

    SetCharacterControlled(MainWorm);
}

void MainMenu::Start()
{
    Level::Start();
}
