#pragma once

#include "../GameObject.h"
#include "./Animations/CharacterRun.h"
#include "GameObject/Components/Input/Input.h"

class CharacterRun;
class Input;
class Camera;

class Character : public GameObject
{
public:
    Character();

    void Update(const float DeltaTime) override;

    Input* GetInputComponent();

    void SetInputMovement(const sf::Vector2f NewInputMovement);

    virtual float TakeDamage(const float Damage) { return 0; };

    float MaxWalkSpeed = 500;
    float MinWalkSpeed = 20;

    std::shared_ptr<Camera> CameraComponent;
    
protected:
    std::shared_ptr<Input> InputComponent;

    std::vector<std::shared_ptr<CharacterRun>> CharacterRun;

    sf::Vector2f InputMovement = sf::Vector2f(0, 0);

    sf::Vector2f AxisMoveValue;

    void PerformInputMovement(const float DeltaTime);

    virtual void SetupBindAction() = 0;
};
