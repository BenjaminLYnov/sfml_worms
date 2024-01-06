#include "Level.h"
#include <SFML/Graphics.hpp> // Inclure l'en-tête complet pour l'implémentation
#include "Level.h"
#include "GameObject/Actor/Character/Character.h"
#include "GameObject/Components/Input/Input.h"

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

void Level::ProcessEvents()
{
    if (CharacterControlled)
        if (CharacterControlled->GetInputComponent())
            CharacterControlled->GetInputComponent()->PollActionsEvents();
}

void Level::Update(const float DeltaTime)
{
    for (auto &GameObject : GameObjects)
    {
        GameObject->Update(DeltaTime);
    }
}

void Level::Render(sf::RenderWindow &Window) const
{
    for (const auto &GameObject : GameObjects)
    {
        GameObject->Render(Window);
    }
}

void Level::SetCharacterControlled(std::shared_ptr<Character> NewCharacterControlled)
{
    CharacterControlled = NewCharacterControlled;
}