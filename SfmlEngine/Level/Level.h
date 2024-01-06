#pragma once

#include <vector>
#include "GameObject/GameObject.h"

class Character;

// Forward declaration de sf::RenderWindow
namespace sf
{
    class RenderWindow;
}

class Level
{
public:
    Level();

    virtual void Start();

    // Ajoute un GameObject au niveau
    void AddGameObject(std::shared_ptr<GameObject> GameObject);

    // Gestionnaires d'événements
    virtual void ProcessEvents();

    // Met à jour tous les GameObjects du niveau
    void Update(const float DeltaTime);

    // Effectue le rendu de tous les GameObjects du niveau
    void Render(sf::RenderWindow &Window) const;

    // Assigne le Character que le joueur contrôle dans le level
    void SetCharacterControlled(std::shared_ptr<Character> NewCharacterControlled);

protected:
    std::vector<std::shared_ptr<GameObject>> GameObjects;

    std::shared_ptr<Character> CharacterControlled;
};
