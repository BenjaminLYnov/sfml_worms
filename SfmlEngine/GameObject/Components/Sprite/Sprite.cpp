#include "Sprite.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
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
        Animation->Update(DeltaTime);
}

void Sprite::Render(sf::RenderWindow &Window)
{
    if (!SfmlSprite)
        return;

    // Dessinez le sprite sur la fenêtre SFML
    Window.draw(*SfmlSprite);
}

void Sprite::UpdatePosition()
{
    if (!SfmlSprite)
        return;
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
    if (!Animation)
        return;
    Animation->SetAnimationSpeed(Speed);
}

void Sprite::AddAnimationFrame(const sf::IntRect &Frame)
{
    if (!Animation)
        return;
    Animation->AddAnimationFrame(Frame);
    SetOriginToCenter();
}

void Sprite::SetAnimationFrame(const sf::IntRect &Frame)
{
    if (!Animation)
        return;
    Animation->ResetFrames();
    AddAnimationFrame(Frame);
}

void Sprite::SetOffset(const sf::Vector2f &NewOffset)
{
    if (!SfmlSprite)
        return;
    Offset = NewOffset;
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

void Sprite::SetRotation(const float Rotation)
{
    if (!SfmlSprite)
        return;
    SfmlSprite->setRotation(Rotation);
}

void Sprite::SetTexture(std::shared_ptr<sf::Texture> &TextureToSet)
{
    Texture = TextureToSet;
    if (!Texture)
        return;

    SfmlSprite->setTexture(*Texture);
    SetOriginToCenter();
    Animation->SetSprite(SfmlSprite);
    Animation->ResetFrames();
}

std::shared_ptr<sf::Texture> &Sprite::GetTexture()
{
    return Texture;
}

sf::Vector2f Sprite::GetPosition() const
{
    if (!SfmlSprite)
        return sf::Vector2f(0, 0);
    return SfmlSprite->getPosition();
}
