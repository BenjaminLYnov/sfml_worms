#include "GameManager.h"
#include <SFML/Graphics.hpp> // Inclure l'en-tête complet pour l'implémentation
#include "Level/Level.h"
#include <cstdlib> // Pour la fonction exit
#include <iostream>

GameManager::GameManager()
{
    // Instance la fenêtre de jeu
    InitWindow();
}

void GameManager::Run()
{
    // Vérifier si le level a été instancié
    if (!CurrentLevel)
        return;

    // Vérifier si le fenêtre de jeu a bien été instancié
    if (!Window)
        return;

    // Démarre le level
    CurrentLevel->SetWindow(Window.get());
    CurrentLevel->GM = this;
    CurrentLevel->Start();

    // Instance Clock pour déterminer le Delta Time
    sf::Clock Clock;

    // Boucle de jeu principal
    while (Window->isOpen())
    {
        ProcessEvents();

        Update(Clock.restart().asSeconds());

        CurrentLevel->ManageCollision();

        Render(*Window);
    }
}

void GameManager::AddLevel(const std::string LevelName, std::shared_ptr<Level> NewLevel)
{
    if (!NewLevel || LevelName == "")
        return;
    if (!CurrentLevel)
        CurrentLevel = NewLevel;

    if (HasLevel(LevelName))
        return;

    Levels.insert({LevelName, NewLevel});
}

void GameManager::LoadLevel(const std::string LevelName)
{
    // Level not found
    if (!HasLevel(LevelName))
    {
        std::cout << "Load Level " << LevelName << " Failed\n";
        return;
    }

    CurrentLevel = Levels[LevelName];

    if (!Window)
        return;

    CurrentLevel->SetWindow(Window.get());
    CurrentLevel->GM = this;
    CurrentLevel->Start();
}

void GameManager::SetStartLevel(const std::string LevelName)
{
    if (!HasLevel(LevelName))
        return;
    CurrentLevel = Levels[LevelName];
}

// PRIVATE

void GameManager::InitWindow()
{
    // Création de la fenêtre SFML
    // Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(920, 680), "SFML Window");
    Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(920, 680), "SFML Window");

    // Activer le mode plein écran
    Window->create(sf::VideoMode::getDesktopMode(), "SFML Fullscreen Windowed", sf::Style::Titlebar | sf::Style::Close);

    // Limite les FPS à 60
    Window->setFramerateLimit(60);

    // Désactiver la gestion automatique des événements de fenêtre
    Window->setActive(false);
}

void GameManager::ProcessEvents()
{
    sf::Event Event;
    while (Window->pollEvent(Event))
    {
        if (Event.type == sf::Event::Closed)
            Window->close();
        else if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape)
            Window->close();
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

void GameManager::Render(sf::RenderWindow &Window) const
{
    // Rendu des objets
    if (!CurrentLevel)
        return;
    Window.clear();
    CurrentLevel->Render(Window);
    Window.display();
}

bool GameManager::HasLevel(const std::string LevelName) const
{
    if (Levels.find(LevelName) == Levels.end())
        return false;
    return true;
}
