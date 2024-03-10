#include "GameManager/GameManager.h"
#include "Levels/MainMenu/MainMenu.h"
#include "Levels/MainMenu/LevelRules.h"
#include "Levels/Party.h"
#include "Levels/Graph/GraphEdition.h"


int main()
{
    // Instance Game Manager
    std::unique_ptr<GameManager> SGameManager = std::make_unique<GameManager>();

    // Add Level
    SGameManager->AddLevel("Party", std::make_shared<Party>());
    SGameManager->AddLevel("GraphEdition", std::make_shared<GraphEdition>());
    SGameManager->SetStartLevel("GraphEdition");

    // Run Game Loop
    SGameManager->Run();

    return 0;
}
