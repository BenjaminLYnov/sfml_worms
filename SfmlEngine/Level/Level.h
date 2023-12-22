#pragma once

#include <vector>
#include "GameObject/GameObject.h"

// Forward declaration de sf::RenderWindow
namespace sf {
    class RenderWindow;
}

class Level {
public:
    Level();

    virtual void Start();

    // Ajoute un GameObject au niveau
    void AddGameObject(std::shared_ptr<GameObject> GameObject);

    // Met à jour tous les GameObjects du niveau
    void Update(const float DeltaTime);

    // Effectue le rendu de tous les GameObjects du niveau
    void Render(sf::RenderWindow& Window);

protected:
    std::vector<std::shared_ptr<GameObject>> GameObjects;
};
