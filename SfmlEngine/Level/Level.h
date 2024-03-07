#pragma once

#include <vector>
#include "GameObject/GameObject.h"
#include "UI/Canvas.h"

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

    void AddCanvas(std::shared_ptr<Canvas> Canvas);

    std::vector<std::shared_ptr<GameObject>> GetAllGameObjects();

    template <typename T>
    std::vector<T *> GetAllGameObjectByClass();

    template <typename T>
    T *SpawnGameObject(const sf::Vector2f Location = sf::Vector2f(0, 0), const sf::Vector2f Scale = sf::Vector2f(1, 1), const float Rotation = 0.f);

    // Gestionnaires d'événements
    virtual void ProcessEvents();

    // Met à jour tous les GameObjects du niveau
    virtual void Update(const float DeltaTime);

    // Effectue le rendu de tous les GameObjects du niveau
    virtual void Render(sf::RenderWindow &Window) const;

    //Effectue le rendu de l'UI du niveau
    void RenderUI(sf::RenderWindow &Window) const;

    // Assigne le Character que le joueur contrôle dans le level
    void SetCharacterControlled(Character *NewCharacterControlled);

    void OnCollision();

    void RemoveGameObject(GameObject *GameObjectToRemove);

protected:
    std::vector<std::shared_ptr<GameObject>> GameObjects;
    std::vector<std::shared_ptr<Canvas>> Canvases;
    Character *CharacterControlled;

private:
};

#include "Level.tpp"
