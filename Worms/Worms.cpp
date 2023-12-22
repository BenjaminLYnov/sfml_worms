#include <iostream>
#include "Levels/MainMenu/MainMenu.h"
#include "GameManager/GameManager.h"

int main()
{
    // Instance Game Manager
    std::shared_ptr<GameManager> SGameManager = std::make_unique<GameManager>();

    // Add Level
    SGameManager->AddLevel(std::make_shared<MainMenu>());

    // Run Game Loop
    SGameManager->Run();

    return 0;
}
