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
