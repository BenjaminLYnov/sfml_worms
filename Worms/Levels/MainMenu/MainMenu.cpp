#include "MainMenu.h"
#include <iostream>
#include "Characters/Worm/Worm.h"

MainMenu::MainMenu()
{
    // Instance Main Character 
    std::shared_ptr<Worm> MainWorm = std::make_shared<Worm>();
    AddGameObject(MainWorm);

    SetCharacterControlled(MainWorm);
}

void MainMenu::Start()
{
    Level::Start();
}
