#include "Level.h"
#include <SFML/Graphics.hpp> // Inclure l'en-tête complet pour l'implémentation
#include "GameObject/Character/Character.h"
#include "GameObject/Components/Input/Input.h"
#include "GameObject/Components/Collider/ICollider.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "iostream"

Level::Level()
{
    DeltaSecond = 0;
}

void Level::Start()
{
    for (std::shared_ptr<GameObject> Go : GameObjects)
        if (Go)
            Go->Start();
}

void Level::AddGameObject(std::shared_ptr<GameObject> GameObject)
{
    if (!GameObject)
        return;
    GameObjects.push_back(GameObject);
    GameObject->SetLevel(this);
}

std::vector<std::shared_ptr<GameObject>> Level::GetAllGameObjects()
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
    DeltaSecond = DeltaTime;
    for (std::shared_ptr<GameObject> Go : GameObjects)
        if (Go)
            Go->Update(DeltaTime);
}

void Level::Render(sf::RenderWindow &Window) const
{
    for (std::shared_ptr<GameObject> Go : GameObjects)
        if (Go)
            Go->Render(Window);
}

void Level::SetCharacterControlled(std::shared_ptr<Character> NewCharacterControlled)
{
    if (!NewCharacterControlled)
        return;
    CharacterControlled = NewCharacterControlled;
    CharacterControlled->GetInputComponent()->SetNeedKeyReleaseFirst(true);
}

void Level::ManageCollision()
{
    // Parcours tous les game object du level
    for (std::shared_ptr<GameObject> GameObjectToCheckCollision : GameObjects)
    {
        if (!GameObjectToCheckCollision)
            continue;

        // Récupère le collider du game object actuelle de la boucle
        ICollider *ColliderToCheck = GameObjectToCheckCollision->GetComponent<ICollider>();
        // std::shared_ptr<ICollider> ColliderToCheck = GameObjectToCheckCollision->GetComponent<ICollider>();

        // Vérifier si le collider est valide
        if (!ColliderToCheck)
            continue;

        // Les parcourir tous les Game Objects en ignorant lui même
        for (std::shared_ptr<GameObject> OtherGameObject : GameObjects)
        {

            if (!OtherGameObject)
                continue;

            if (OtherGameObject == GameObjectToCheckCollision)
                continue;

            // Récupère le Collider de l'autre game object actuelle de la boucle
            ICollider *OtherCollider = OtherGameObject->GetComponent<ICollider>();

            // Vérifier si l'autre collider est valide
            if (!OtherCollider)
                continue;

            // Exécuter le test de collision, en cas de collision -> applique les logiques en conséquences (callbacks, annulation de collision)
            ColliderToCheck->ManageCollision(OtherCollider);
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

float Level::GetWorldDeltaSecond() const
{
    return DeltaSecond;
}

std::shared_ptr<Character> Level::GetCharacterControlled()
{
    return CharacterControlled;
}

// PRIVATE
