#include "MainMenu.h"
#include <iostream>
#include "Characters/Worm/Worm.h"

MainMenu::MainMenu()
{
    AddGameObject(std::make_shared<Worm>());
}

void MainMenu::Start()
{
    Level::Start();
}
