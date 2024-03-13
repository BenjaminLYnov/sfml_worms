#include "Level.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject/Character/Character.h"
#include "GameObject/Components/Input/Input.h"
#include "GameObject/Components/Collider/ICollider.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "iostream"
#include "GameManager/GameManager.h"
#include <SFML/Graphics/RectangleShape.hpp>

#include "UI/Canvas.h"

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

void Level::RenderUI(sf::RenderWindow& Window) const
{
    for (std::shared_ptr<Canvas> canva : CanvasList)
    {
        if (canva)
        {
            canva->UpdateRect(Window.getView().getViewport());
            canva->Draw(Window);
        }
    }
}

void Level::AddGameObject(std::shared_ptr<GameObject> GameObject)
{
    if (!GameObject)
        return;
    GameObjects.push_back(GameObject);
    GameObject->SetLevel(this);
}

void Level::AddCanvas(std::shared_ptr<Canvas> Canvas)
{
    if(!Canvas)
        return;
    CanvasList.push_back(Canvas);
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

void Level::SetCharacterControlled(std::shared_ptr<Character> NewCharacterControlled)
{
    CharacterControlled = NewCharacterControlled;
    if (CharacterControlled)
        CharacterControlled->GetInputComponent()->SetNeedKeyReleaseFirst(true);
}

void Level::ManageCollision()
{
    ManageCollisionByGameObjects(GameObjects);
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

// PROTECTED

void Level::ManageCollisionByGameObjects(std::vector<std::shared_ptr<GameObject>> GameObjectsToManage)
{
    if (GameObjectsToManage.size() <= 1)
        return;

    for (size_t i = 0; i < GameObjectsToManage.size(); ++i)
    {
        if (!GameObjectsToManage[i])
            continue;

        // Récupère le collider du game object actuelle de la boucle
        ICollider *ColliderToCheck = GameObjectsToManage[i]->GetComponent<ICollider>();

        if (!ColliderToCheck)
            continue;

        if (!ColliderToCheck->bEnableCollision)
            continue;

        for (size_t j = i + 1; j < GameObjectsToManage.size(); ++j)
        {
            if (!GameObjectsToManage[j])
                continue;

            // Récupère le Collider de l'autre game object actuelle de la boucle
            ICollider *OtherCollider = GameObjectsToManage[j]->GetComponent<ICollider>();

            if (!OtherCollider)
                continue;

            if (!OtherCollider->bEnableCollision)
                continue;

            // Exécuter le test de collision, en cas de collision -> applique les logiques en conséquences (callbacks, annulation de collision)
            ColliderToCheck->ManageCollision(OtherCollider);
        }
    }
}

void Level::InitZone()
{
    for (int Line = 0; Line < Lines; Line++)
    {
        for (int Col = 0; Col < Cols; Col++)
        {
            std::shared_ptr<SquareCollider> Zone = std::make_shared<SquareCollider>();
            Zone->Start();
            Zone->SetSize(ZoneSize);
            Zone->Shape->setPosition(sf::Vector2f(ZoneSize.y * Col, ZoneSize.x * Line));
            Zones.push_back(Zone);
        }
    }
}

// PRIVATE

std::vector<std::shared_ptr<GameObject>> Level::GetGameObjectsByZone(std::shared_ptr<SquareCollider> &ZoneToGetGameObjects)
{
    std::vector<std::shared_ptr<GameObject>> GameObjectsToFind;

    if (!ZoneToGetGameObjects)
        return GameObjectsToFind;

    std::shared_ptr<ICollider> ZoneCollider = std::dynamic_pointer_cast<ICollider>(ZoneToGetGameObjects);

    for (std::shared_ptr<GameObject> Go : GameObjects)
    {
        if (!Go)
            continue;

        // Récupère le collider du game object actuelle de la boucle
        ICollider *ColliderToCheck = Go->GetComponent<ICollider>();

        if (!ColliderToCheck)
            continue;

        if (!ColliderToCheck->bEnableCollision)
            continue;

        HitResult Hit = ZoneCollider->TestCollision(ColliderToCheck);
        
        if (Hit.bIsOnCollision)
            GameObjectsToFind.push_back(Go);
    }

    return GameObjectsToFind;
}
