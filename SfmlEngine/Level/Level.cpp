#include "Level.h"
#include <SFML/Graphics.hpp> // Inclure l'en-tête complet pour l'implémentation
#include "Level.h"

Level::Level()
{
    // Initialisation du niveau, si nécessaire
}

void Level::Start()
{
    for (auto &GameObject : GameObjects)
    {
        GameObject->Start();
    }
}

void Level::AddGameObject(std::shared_ptr<GameObject> GameObject)
{
    GameObjects.push_back(GameObject);
}

void Level::Update(const float deltaTime)
{
    for (auto &GameObject : GameObjects)
    {
        GameObject->Update(deltaTime);
    }
}

void Level::Render(sf::RenderWindow &Window)
{
    for (const auto &GameObject : GameObjects)
    {
        GameObject->Render(Window);
    }
}