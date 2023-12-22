#include "GameObject.h"
#include "./Components/IComponent.h"
#include "./Components/Transform/Transform.h"
#include <SFML/Graphics.hpp> // Inclure l'en-tête complet pour l'implémentation

GameObject::GameObject()
{
    TransformComponent = std::make_shared<Transform>();
    AddComponent(TransformComponent);
}

void GameObject::Start()
{
    for (const auto &Component : Components)
    {
        Component->Start();
    }
}

void GameObject::Update(const float DeltaTime)
{
    for (const auto &Component : Components)
    {
        Component->Update(DeltaTime);
    }
}

void GameObject::Render(sf::RenderWindow &Window) const
{
    for (const auto &Component : Components)
    {
        Component->Render(Window);
    }
}

void GameObject::AddComponent(std::shared_ptr<IComponent> Component)
{
    Components.push_back(Component);
    Component->SetOwner(this);
}

template <typename T>
std::shared_ptr<T> GameObject::GetComponent() const
{
    for (const auto &Component : Components)
    {
        std::shared_ptr<T> derived = std::dynamic_pointer_cast<T>(Component);
        if (derived != nullptr)
        {
            return derived;
        }
    }
    return nullptr;
}

void GameObject::SetPosition(const sf::Vector2f &Position)
{
    TransformComponent->SetPosition(Position);
}

void GameObject::SetScale(const sf::Vector2f &Scale)
{
    TransformComponent->SetScale(Scale);
}

void GameObject::SetRotation(float Rotation)
{
    TransformComponent->SetRotation(Rotation);
}

sf::Vector2f GameObject::GetPosition() const
{
    return TransformComponent->GetPosition();
}

sf::Vector2f GameObject::GetScale() const
{
    return TransformComponent->GetScale();
}

float GameObject::GetRotation() const
{
    return TransformComponent->GetRotation();
}

std::shared_ptr<Transform> GameObject::GetTransform() const
{
    return TransformComponent;
}
