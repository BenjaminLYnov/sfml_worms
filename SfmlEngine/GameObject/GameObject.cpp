#include "GameObject.h"
#include "./Components/IComponent.h"
#include "./Components/Transform/Transform.h"
#include "./Components/Collider/ICollider.h"
#include "./Components/Sprite/Sprite.h"
#include <SFML/Graphics.hpp> // Inclure l'en-tête complet pour l'implémentation
#include "Level/Level.h"
#include <iostream>

GameObject::GameObject()
{
    WorldTransformComponent = std::make_shared<Transform>();
    RelativeTransformComponent = std::make_shared<Transform>();
    RelativeTransformComponent = std::make_shared<Transform>();
    AnimationComponent = std::make_shared<Sprite>();

    AddComponent(WorldTransformComponent.get());
    AddComponent(RelativeTransformComponent.get());
    AddComponent(AnimationComponent.get());
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

// void GameObject::AddComponent(std::shared_ptr<IComponent> Component)
void GameObject::AddComponent(IComponent *Component)
{
    if (!Component)
        return;
    Components.push_back(Component);
    Component->SetOwner(this);
}

void GameObject::RemoveComponent(IComponent *ComponentToRemove)
{
    if (!ComponentToRemove)
        return;

    auto It = std::find(Components.begin(), Components.end(), ComponentToRemove);
    if (It != Components.end())
    {
        Components.erase(It);
    }
}

void GameObject::AddWorldPosition(const sf::Vector2f &AmountPosition)
{
    WorldTransformComponent->SetPosition(GetWorldPosition() + AmountPosition);
    UpdateComponentsPosition();
}

void GameObject::AddRelativePosition(const sf::Vector2f &AmountPosition)
{
    RelativeTransformComponent->SetPosition(GetRelativePosition() + AmountPosition);
    UpdateComponentsPosition();
}

void GameObject::SetWorldPosition(const sf::Vector2f &Position)
{
    WorldTransformComponent->SetPosition(Position);
    UpdateComponentsPosition();
}

void GameObject::SetRelativePosition(const sf::Vector2f &Position)
{
    if (RelativeTransformComponent)
    {
        RelativeTransformComponent->SetPosition(Position);
        UpdateComponentsPosition();
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

void GameObject::SetName(const std::string &NewName)
{
    Name = NewName;
}

std::string GameObject::GetName() const
{
    return Name;
}

void GameObject::SetLevel(Level *Level)
{
    OwnerLevel = Level;
}

Level *GameObject::GetWorld()
{
    return OwnerLevel;
}

void GameObject::Destroy(GameObject *GameObjectToDestroy)
{
    if (!OwnerLevel)
        return;

    if (!GameObjectToDestroy)
        GameObjectToDestroy = this;

    if (!GameObjectToDestroy)
        return;

    OwnerLevel->RemoveGameObject(GameObjectToDestroy);
}

void GameObject::SwitchAnimation(std::shared_ptr<Sprite> NewAnimation)
{
    if (!NewAnimation)
        return;

    if (!AnimationComponent)
        return;

    if (AnimationComponent.get())
        RemoveComponent(AnimationComponent.get());

    AnimationComponent = NewAnimation;
    AddComponent(AnimationComponent.get());
}

// PRIVATE

void GameObject::UpdateComponentsPosition()
{
    // Update components Position as Well
    for (const auto &Component : Components)
    {
        Component->UpdatePosition();
    }
}
