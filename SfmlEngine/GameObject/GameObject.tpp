#include "GameObject.h"
#include "Components/IComponent.h"
#include "Level/Level.h"

template <typename T>
std::shared_ptr<T> GameObject::GetComponent() const
{
    for (const auto &Component : Components)
    {
        if (!Component)
            continue;
        std::shared_ptr<T> Derived = std::dynamic_pointer_cast<T>(Component);
        if (Derived)
            return Derived;
    }
    return nullptr;
}

template <typename T>
std::vector<std::shared_ptr<T>> GameObject::GetAllGameObjectByClass()
{
    static_assert(std::is_base_of<GameObject, T>::value, "T must be derived from GameObject");

    std::vector<std::shared_ptr<GameObject>> GameObjects = GetAllGameObjects();

    std::vector<std::shared_ptr<T>> filteredObjects;
    for (auto &obj : GameObjects)
    {
        auto castedPtr = std::dynamic_pointer_cast<T>(obj);
        if (castedPtr)
        {
            filteredObjects.push_back(castedPtr);
        }
    }
    return filteredObjects;
}

template <typename T>
std::shared_ptr<T> GameObject::SpawnGameObject(const sf::Vector2f Location, const sf::Vector2f Scale, const float Rotation)
{
    static_assert(std::is_base_of<GameObject, T>::value, "T must be derived from GameObject");

    // Instance le nouveau GameObject
    std::shared_ptr<T> NewGameObject = std::make_shared<T>();

    // Vérifier si le OwnerLevel est valide
    if (!OwnerLevel)
        return NewGameObject;

    // Cast à GameObject
    // NewGameObject = std::dynamic_pointer_cast<GameObject>(NewGameObject);
    NewGameObject->Start();
    NewGameObject->SetWorldPosition(Location);
    NewGameObject->SetWorldRotation(Rotation);
    NewGameObject->SetWorldScale(Scale);

    // Ajouter le dans le level
    OwnerLevel->AddGameObject(NewGameObject);

    // Return le nouveau GameObject
    return NewGameObject;
}