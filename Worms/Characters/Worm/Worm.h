#pragma once

#include "GameObject/Actor/Character/Character.h"

class Sprite;
class InputAction;

class Worm : public Character
{
public:
    Worm();

    void Start() override;

    void Update(const float DeltaTime) override;

    void Render(sf::RenderWindow &Window) const override;

protected:
    void InitAnimations();

#pragma region InputAction
    virtual void Move(const sf::Vector2f Value);
    virtual void Jump();
    //virtual void Fire();
    
#pragma endregion

    virtual void Started();
    virtual void Triggered();
    virtual void Completed();

    void SetupBindAction() override;

    int TakeDamage(const int Damage);

    void OnDestroy();

private:
    // Sprites Animation
    std::shared_ptr<Sprite> CurrentSprite;
    std::shared_ptr<Sprite> IdleA;
    std::shared_ptr<Sprite> WalkA;
    std::shared_ptr<Sprite> WinnnerA;

    // Input Action
    std::shared_ptr<InputAction> IaMove;
    std::shared_ptr<InputAction> IaJump;
    //std::shared_ptr<InputAction> IaFire;

    int Health;

    bool bIsAlive;
};
