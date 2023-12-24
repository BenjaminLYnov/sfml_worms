#include "GameObject.h"
#include "./Components/IComponent.h"
#include "./Components/Transform/Transform.h"
#include <SFML/Graphics.hpp> // Inclure l'en-tête complet pour l'implémentation

GameObject::GameObject()
{
    WorldTransformComponent = std::make_shared<Transform>();
    RelativeTransformComponent = std::make_shared<Transform>();
    AddComponent(WorldTransformComponent);
    AddComponent(RelativeTransformComponent);
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

void GameObject::SetWorldPosition(const sf::Vector2f &Position)
{
    WorldTransformComponent->SetPosition(Position);
}

void GameObject::SetRelativePosition(const sf::Vector2f &Position)
{
    if (RelativeTransformComponent)
    {
        RelativeTransformComponent->SetPosition(Position);
    }
}

void GameObject::SetWorldScale(const sf::Vector2f &Scale)
{
    WorldTransformComponent->SetScale(Scale);
}

void GameObject::SetRelativeScale(const sf::Vector2f &Scale)
{
    if (RelativeTransformComponent)
    {
        RelativeTransformComponent->SetScale(Scale);
    }
}

void GameObject::SetWorldRotation(const float Rotation)
{
    WorldTransformComponent->SetRotation(Rotation);
}

void GameObject::SetRelativeRotation(const float Rotation)
{
    if (RelativeTransformComponent)
    {
        RelativeTransformComponent->SetRotation(Rotation);
    }
}

sf::Vector2f GameObject::GetWorldPosition() const
{
    return WorldTransformComponent->GetPosition();
}

sf::Vector2f GameObject::GetRelativePosition() const
{
    return RelativeTransformComponent ? RelativeTransformComponent->GetPosition() : sf::Vector2f();
}

sf::Vector2f GameObject::GetWorldScale() const
{
    return WorldTransformComponent->GetScale();
}

sf::Vector2f GameObject::GetRelativeScale() const
{
    return RelativeTransformComponent ? RelativeTransformComponent->GetScale() : sf::Vector2f();
}

float GameObject::GetWorldRotation() const
{
    return WorldTransformComponent->GetRotation();
}

float GameObject::GetRelativeRotation() const
{
    return RelativeTransformComponent ? RelativeTransformComponent->GetRotation() : 0.0f;
}

std::shared_ptr<Transform> GameObject::GetWorldTransform() const
{
    return WorldTransformComponent;
}
