#include "GameObject.h"
#include "Components/IComponent.h"
#include "Level/Level.h"

template <typename T>
// std::shared_ptr<T> GameObject::GetComponent() const
T* GameObject::GetComponent() const
{
    for (const auto &Component : Components)
    {
        if (!Component)
            continue;
        // std::shared_ptr<T> Derived = std::dynamic_pointer_cast<T>(Component);
        T* Derived = dynamic_cast<T*>(Component);
        if (Derived)
            return Derived;
    }
    return nullptr;
}

template <typename T>
void GameObject::RemoveComponent()
{
    auto it = std::find_if(Components.begin(), Components.end(),
                           [](IComponent* component) { return dynamic_cast<T*>(component) != nullptr; });

    if (it != Components.end()) {
        Components.erase(it);
    }
}

