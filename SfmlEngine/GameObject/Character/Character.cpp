#include "Character.h"
#include "GameObject/Components/Input/Input.h"
#include "Math/Vector/Vector.h"
#include <iostream>

Character::Character() : GameObject()
{
    InputComponent = std::make_shared<Input>();
    AddComponent(InputComponent.get());
}

void Character::Update(const float DeltaTime)
{
    GameObject::Update(DeltaTime);
    PerformInputMovement(DeltaTime);
}

Input* Character::GetInputComponent()
{
    return InputComponent.get();
}

void Character::SetInputMovement(const sf::Vector2f NewInputMovement)
{
    InputMovement = NewInputMovement;
}

// PROTECTED

void Character::PerformInputMovement(const float DeltaTime)
{
    AddWorldPosition(InputMovement * MaxWalkSpeed * DeltaTime);
    SetInputMovement(sf::Vector2f(0, 0));
}