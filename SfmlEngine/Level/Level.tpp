#include "Level.h"

template <typename T>
std::vector<std::shared_ptr<T>> Level::GetAllGameObjectByClass()
{
    static_assert(std::is_base_of<GameObject, T>::value, "T must be derived from GameObject");

    std::vector<std::shared_ptr<T>> GameObjectsOfClass;

    for (auto &obj : GameObjects)
    {
        auto castedPtr = std::dynamic_pointer_cast<T>(obj);
        if (castedPtr)
        {
            GameObjectsOfClass.push_back(castedPtr);
        }
    }

    return GameObjectsOfClass;
}

template <typename T>
T *Level::SpawnGameObject(const sf::Vector2f Location, const sf::Vector2f Scale, const float Rotation)
{
    static_assert(std::is_base_of<GameObject, T>::value, "T must be derived from GameObject");

    // Instance le nouveau GameObject
    std::shared_ptr<T> NewGameObject = std::make_shared<T>();

    // Cast à GameObject
    NewGameObject->Start();
    NewGameObject->SetWorldPosition(Location);
    NewGameObject->SetWorldRotation(Rotation);
    NewGameObject->SetWorldScale(Scale);

    // Ajouter le dans le level
    AddGameObject(NewGameObject);

    // Return le nouveau GameObject
    return NewGameObject.get();
}