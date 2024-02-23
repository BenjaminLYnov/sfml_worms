#include "Level.h"
#include <SFML/Graphics.hpp> // Inclure l'en-tête complet pour l'implémentation
#include "GameObject/Character/Character.h"
#include "GameObject/Components/Input/Input.h"
#include "GameObject/Components/Collider/ICollider.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "iostream"

Level::Level()
{
    // Initialisation du niveau, si nécessaire
}

void Level::Start()
{
    for (auto &GameObject : GameObjects)
        GameObject->Start();
}

void Level::AddGameObject(std::shared_ptr<GameObject> GameObject)
{
    GameObjects.push_back(GameObject);
    GameObject->SetLevel(this);
}

std::vector<std::shared_ptr<GameObject>> &Level::GetGameObjects()
{
    return GameObjects;
}

void Level::ProcessEvents()
{
    if (!CharacterControlled)
        return;
    if (!CharacterControlled->GetInputComponent())
        return;
    CharacterControlled->GetInputComponent()->PollActionsEvents();
}

void Level::Update(const float DeltaTime)
{
    for (auto &GameObject : GameObjects)
        GameObject->Update(DeltaTime);
}

void Level::Render(sf::RenderWindow &Window) const
{
    for (const auto &GameObject : GameObjects)
        GameObject->Render(Window);
}

void Level::SetCharacterControlled(std::shared_ptr<Character> NewCharacterControlled)
{
    CharacterControlled = NewCharacterControlled;
}

void Level::OnCollision()
{
    // Parcours tous les game object du level
    for (auto &GameObjectToCheckCollision : GameObjects)
    {
        if (!GameObjectToCheckCollision)
            continue;

        // Récupère le collider du game object actuelle de la boucle
        std::shared_ptr<ICollider> ColliderToCheck = GameObjectToCheckCollision->GetComponent<ICollider>();

        // Vérifier si le collider est valide
        if (!ColliderToCheck)
            continue;

        // Récupère tous les autres Game Objects
        std::vector<std::shared_ptr<GameObject>> AllOtherGameObject = GetAllOtherGameObject(GameObjectToCheckCollision);

        // Les parcourir tous les autres Game Objects
        for (auto &OtherGameObject : AllOtherGameObject)
        {
            // Récupère le Collider de l'autre game object actuelle de la boucle
            std::shared_ptr<ICollider> OtherCollider = OtherGameObject->GetComponent<ICollider>();

            // Vérifier si l'autre collider est valide
            if (!OtherCollider)
                continue;

            // Exécuter le test de collision, en cas de collision -> applique les logiques en conséquences (callbacks, annulation de collision)
            ColliderToCheck->OnCollision(OtherCollider);
        }
    }
}

void Level::RemoveGameObject(GameObject *GameObjectToRemove)
{
    // Utiliser std::remove_if pour trouver et supprimer l'élément
    GameObjects.erase(std::remove_if(GameObjects.begin(), GameObjects.end(),
                                     [GameObjectToRemove](const std::shared_ptr<GameObject> &ptr)
                                     { return ptr.get() == GameObjectToRemove; }),
                      GameObjects.end());
}

// PRIVATE

std::vector<std::shared_ptr<GameObject>> Level::GetAllOtherGameObject(std::shared_ptr<GameObject> GameObjectToIgnore)
{
    std::vector<std::shared_ptr<GameObject>> AllOtherGameObject;
    for (auto &GameObjectToAdd : GameObjects)
        if (GameObjectToAdd != GameObjectToIgnore)
            AllOtherGameObject.push_back(GameObjectToAdd);
    return AllOtherGameObject;
}