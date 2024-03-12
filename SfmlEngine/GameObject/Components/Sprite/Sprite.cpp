#include "Sprite.h"
#include <SFML/Graphics.hpp> // Incluez l'en-tête complet pour l'implémentation de la SFML
#include <iostream>
#include "GameObject/GameObject.h"
#include "AnimatedSprite.h"

Sprite::Sprite()
{
    // Initialiser les instances
    Texture = std::make_shared<sf::Texture>();
    SfmlSprite = std::make_shared<sf::Sprite>();
    Animation = std::make_shared<AnimatedSprite>();
}

void Sprite::Start()
{
}

void Sprite::Update(const float DeltaTime)
{
    if (Animation)
    {
        Animation->Update(DeltaTime);
    }
}

void Sprite::UpdatePosition()
{
    sf::Vector2f NewPosition = GetOwner()->GetWorldPosition() + GetOwner()->GetRelativePosition() + Offset;
    SfmlSprite->setPosition(NewPosition);
}

bool Sprite::LoadTextureFromMemory(const unsigned char *Data, size_t Size)
{
    if (!Data && Size == 0)
        return false;

    if (!Texture->loadFromMemory(Data, Size))
        return false;

    // Améliorer la qualité de rendu de la texture
    Texture->setSmooth(true);

    // Initialisez le sprite avec la texture chargée
    SfmlSprite = std::make_shared<sf::Sprite>(*Texture);
    SetOriginToCenter();
    Animation->SetSprite(SfmlSprite);
    Animation->ResetFrames();

    return true; // Chargement réussi
}

void Sprite::SetAnimationSpeed(const float Speed)
{
    Animation->SetAnimationSpeed(Speed);
}

void Sprite::AddAnimationFrame(const sf::IntRect &Frame)
{
    Animation->AddAnimationFrame(Frame);
    SetOriginToCenter();
}

void Sprite::SetOffset(const sf::Vector2f &NewOffset)
{
    Offset = NewOffset;
    if (!SfmlSprite)
        return;
    SfmlSprite->setPosition(GetOwner()->GetWorldPosition() + Offset);
}

void Sprite::SetOriginToCenter()
{
    if (!SfmlSprite)
        return;
    sf::IntRect Bounds = SfmlSprite->getTextureRect();
    SfmlSprite->setOrigin(Bounds.width * 0.5, Bounds.height * 0.5);
}

void Sprite::ResetAnimation()
{
    if (!Animation)
        return;
    Animation->ResetFrames();
    Animation->SetSprite(std::shared_ptr<sf::Sprite>());
}

void Sprite::SetScale(const sf::Vector2f Scale)
{
    if (!SfmlSprite)
        return;
    SfmlSprite->setScale(Scale);
}

sf::Vector2f Sprite::GetPosition() const
{
    if (!SfmlSprite)
        return sf::Vector2f(0, 0);
    return SfmlSprite->getPosition();
}

void Sprite::Render(sf::RenderWindow &Window)
{
    if (!SfmlSprite)
        return;

    // Dessinez le sprite sur la fenêtre SFML
    Window.draw(*SfmlSprite);
}
