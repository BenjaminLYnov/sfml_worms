#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/Components/Collider/TriangleCollider.h"
#include "GameObject/GameObject.h"
#include "Items/Weapons/Weapon.h"
#include "GameObject/Components/Sprite/Sprite.h"

Cell::Cell(const sf::Vector2f Size) : GameObject()
{
    SquareColliderComponent = std::make_shared<SquareCollider>();
    TriangleLeftColliderComponent = std::make_shared<TriangleCollider>();
    TriangleRightColliderComponent = std::make_shared<TriangleCollider>();

    SquareColliderComponent->AddCallback(ECollisionEvent::Enter, this, &Cell::OnCollisionEnter);
    TriangleLeftColliderComponent->AddCallback(ECollisionEvent::Enter, this, &Cell::OnCollisionEnter);
    TriangleRightColliderComponent->AddCallback(ECollisionEvent::Enter, this, &Cell::OnCollisionEnter);

    SquareColliderComponent->SetMobility(EMobility::Static);
    TriangleLeftColliderComponent->SetMobility(EMobility::Static);
    TriangleRightColliderComponent->SetMobility(EMobility::Static);

    Shape = std::make_shared<sf::RectangleShape>();
    SetSize(Size);

    // Définit la couleur de remplissage du rectangle en transparent
    Shape->setFillColor(sf::Color::Blue);

    // Définit l'épaisseur de la bordure du rectangle
    Shape->setOutlineThickness(0.5);

    // Définit une couleur pour la bordure, par exemple, verte
    Shape->setOutlineColor(sf::Color::Black);
}

void Cell::Start()
{
    GameObject::Start();
}

void Cell::Update(const float DeltaTime)
{
    GameObject::Update(DeltaTime);

    Shape->setPosition(GetWorldPosition());
}

void Cell::Render(sf::RenderWindow &Window) const
{
       if (Shape)
        Window.draw(*Shape);
    GameObject::Render(Window);
}

void Cell::SetSize(const sf::Vector2f &NewSize)
{
    if (!Shape)
        return;
    Shape->setSize(NewSize);
    Shape->setOrigin(NewSize.x / 2, NewSize.y / 2);

    SquareColliderComponent->SetSize(NewSize);
    TriangleRightColliderComponent->SetPoints(sf::Vector2f(NewSize.x, 0), sf::Vector2f(NewSize.x, NewSize.y), sf::Vector2f(0, NewSize.y));
    TriangleLeftColliderComponent->SetPoints(sf::Vector2f(0, 0), sf::Vector2f(NewSize.x, NewSize.y), sf::Vector2f(0, NewSize.y));
}

bool Cell::IsSelected(const sf::Vector2f Position) const
{
    if (!Shape)
        return false;
    return Shape->getLocalBounds().contains(Position);
}

void Cell::SetCollision(const bool bCollision)
{
    SquareColliderComponent->bEnableCollision = bCollision;
    TriangleLeftColliderComponent->bEnableCollision = bCollision;
    TriangleRightColliderComponent->bEnableCollision = bCollision;
}

void Cell::SetCellType(const ECellType NewCellType)
{
    CellType = NewCellType;

    RemoveComponent<ICollider>();

    switch (CellType)
    {
    case ECellType::Square:
        AddComponent(SquareColliderComponent.get());
        SquareColliderComponent->Start();
        AnimationComponent->SetAnimationFrame(sf::IntRect(40, 403, 333, 333));
        AnimationComponent->SetScale(sf::Vector2f(0.12, 0.12));
        // AnimationComponent->SetScale(sf::Vector2f(0.3, 0.3));
        AnimationComponent->SetRotation(0);
        break;
    case ECellType::TriangleLeft:
        AddComponent(TriangleLeftColliderComponent.get());
        TriangleLeftColliderComponent->Start();
        AnimationComponent->SetAnimationFrame(sf::IntRect(638, 424, 111, 111));
        AnimationComponent->SetScale(sf::Vector2f(0.35, 0.35));
        AnimationComponent->SetRotation(180);
        break;
    case ECellType::TriangleRight:
        AddComponent(TriangleRightColliderComponent.get());
        TriangleRightColliderComponent->Start();
        AnimationComponent->SetAnimationFrame(sf::IntRect(800, 424, 111, 111));
        AnimationComponent->SetRotation(180);
        AnimationComponent->SetScale(sf::Vector2f(0.35, 0.35));
        break;
    default:
        AnimationComponent->SetAnimationFrame();
        break;
    }
}

// PROTECTED

void Cell::OnCollisionEnter(GameObject *GameObjectHited)
{
    if (dynamic_cast<Weapon *>(GameObjectHited))
        Destroy();
}
