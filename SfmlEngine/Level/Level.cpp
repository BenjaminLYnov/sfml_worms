#include "Level.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject/Character/Character.h"
#include "GameObject/Components/Input/Input.h"
#include "GameObject/Components/Collider/ICollider.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "iostream"
#include "GameManager/GameManager.h"

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
        if (Go != nullptr)
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
    CharacterControlled = NewCharacterControlled;
    if (CharacterControlled)
        CharacterControlled->GetInputComponent()->SetNeedKeyReleaseFirst(true);
}

void Level::ManageCollision()
{
    std::vector<std::shared_ptr<GameObject>> AllGameObjects = GameObjects;

    for (size_t i = 0; i < AllGameObjects.size(); ++i)
    {
        if (!AllGameObjects[i])
            continue;

        // Récupère le collider du game object actuelle de la boucle
        ICollider *ColliderToCheck = AllGameObjects[i]->GetComponent<ICollider>();

        if (!ColliderToCheck)
            continue;

        if (!ColliderToCheck->bEnableCollision)
            continue;

        for (size_t j = i + 1; j < AllGameObjects.size(); ++j)
        {
            if (!AllGameObjects[j])
                continue;

            // Récupère le Collider de l'autre game object actuelle de la boucle
            ICollider *OtherCollider = AllGameObjects[j]->GetComponent<ICollider>();

            if (!OtherCollider)
                continue;

            if (!OtherCollider->bEnableCollision)
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

void Level::SetWindow(sf::RenderWindow *_Window)
{
    Window = _Window;
}

sf::RenderWindow *Level::GetWindow()
{
    return Window;
}

std::shared_ptr<Character> Level::GetCharacterControlled()
// Character* Level::GetCharacterControlled()
{
    return CharacterControlled;
}

// PRIVATE
