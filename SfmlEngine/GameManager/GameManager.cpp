#include "GameManager.h"
#include <SFML/Graphics.hpp> // Inclure l'en-tête complet pour l'implémentation
#include "Level/Level.h"
#include <cstdlib> // Pour la fonction exit
#include <iostream>

GameManager::GameManager()
{
    // Initialisation supplémentaire si nécessaire
}

void GameManager::Run()
{
    // Vérifier si le level a été instancié
    if (!CurrentLevel)
        return;

    // Instance la fenêtre de jeu
    InitWindow();

    // Vérifier si le fenêtre de jeu a bien été instancié
    if (!Window)
        return;

    // Démarre le level
    CurrentLevel->Start();

    // Instance Clock pour déterminer le Delta Time
    sf::Clock Clock;

    // Boucle de jeu principal
    while (Window->isOpen())
    {
        ProcessEvents();
        Update(Clock.restart().asSeconds());
        Render(*Window);
    }
}

void GameManager::AddLevel(std::shared_ptr<Level> NewLevel)
{
    if (!NewLevel)
        return;

    if (!CurrentLevel)
        CurrentLevel = NewLevel;

    Levels.push_back(NewLevel);
}

// void GameManager::SaveGame(const std::string& filename, const GameData& data) {
//     std::ofstream outFile(filename);
//     if (!outFile) {
//         std::cerr << "Impossible d'ouvrir le fichier pour la sauvegarde." << std::endl;
//         return;
//     }

//     outFile << data.ToJson().dump(4);
// }

// bool GameManager::LoadGame(const std::string& filename, GameData& data) {
//     std::ifstream inFile(filename);
//     if (!inFile) {
//         std::cerr << "Impossible d'ouvrir le fichier pour charger les données." << std::endl;
//         return false;
//     }

//     nlohmann::json jsonData;
//     inFile >> jsonData;
//     data = GameData::FromJson(jsonData);

//     return true;
// }

// PRIVATE

void GameManager::InitWindow()
{
    Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "SFML Window");

    // Limite les FPS à 60
    // Window->setFramerateLimit(60);
    Window->setVerticalSyncEnabled(true);
}

void GameManager::ProcessEvents()
{
    sf::Event Event;
    while (Window->pollEvent(Event))
    {
        if (Event.type == sf::Event::Closed)
            Window->close();

        if (Event.type == sf::Event::MouseWheelScrolled)
        {
            if (Event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                // Traiter le défilement vertical
                float delta = Event.mouseWheelScroll.delta;
                // Faire quelque chose avec delta (positif pour le défilement vers le haut, négatif pour le bas)
                // std::cout << delta << "\n";
            }
            else if (Event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
            {
                // Traiter le défilement horizontal (si pris en charge)
                float delta = Event.mouseWheelScroll.delta;
                // std::cout << delta << "\n";

                // Faire quelque chose avec delta
            }
        }
    }

    if (CurrentLevel)
        CurrentLevel->ProcessEvents();
}

void GameManager::Update(const float DeltaTime)
{
    if (!CurrentLevel)
        return;
    CurrentLevel->Update(DeltaTime);
}

void GameManager::Render(sf::RenderWindow &Window)
{
    // Rendu des objets
    if (!CurrentLevel)
        return;
    Window.clear();
    CurrentLevel->Render(Window);
    Window.display();
}
