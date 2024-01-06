#include "Character.h"
#include "GameObject/Components/Input/Input.h"
#include "Math/Vector/Vector.h"
#include <iostream>

Character::Character() : Actor()
{
    InputComponent = std::make_shared<Input>();
    AddComponent(InputComponent);
}

void Character::Update(const float DeltaTime)
{
    Actor::Update(DeltaTime);
    PerformInputMovement(DeltaTime);
}

std::shared_ptr<Input> Character::GetInputComponent()
{
    return InputComponent;
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