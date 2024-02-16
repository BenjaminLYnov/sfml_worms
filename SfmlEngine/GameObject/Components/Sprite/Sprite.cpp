#include "Sprite.h"
#include <SFML/Graphics.hpp> // Incluez l'en-tête complet pour l'implémentation de la SFML
#include <iostream>
#include "GameObject/GameObject.h"

Sprite::Sprite(const unsigned char *Data, size_t Size)
{
    // Initialiser les instances
    Texture = std::make_shared<sf::Texture>();
    SfmlSprite = std::make_shared<sf::Sprite>();

    // Chargez la texture depuis la memoire
    if (Data && Size > 0)
        LoadTextureFromMemory(Data, Size);
}

void Sprite::Start()
{
    // Code d'initialisation spécifique si nécessaire
}

void Sprite::Update(const float DeltaTime)
{
    AnimatedSprite.Update(DeltaTime);
}

void Sprite::UpdatePosition()
{
    sf::Vector2f NewPosition = GetOwner()->GetWorldPosition() + GetOwner()->GetRelativePosition() + Offset;
    SfmlSprite->setPosition(NewPosition);
}

bool Sprite::LoadTextureFromMemory(const unsigned char *Data, size_t Size)
{
    if (Texture->loadFromMemory(Data, Size))
    {
        // Améliorer la qualité de rendu de la texture
        Texture->setSmooth(true);

        // Initialisez le sprite avec la texture chargée
        SfmlSprite = std::make_shared<sf::Sprite>(*Texture);
        SetOriginToCenter();

        AnimatedSprite.SetSprite(SfmlSprite);

        return true; // Chargement réussi
    }
    // Gérer l'erreur si le chargement échoue
    return false;
}

void Sprite::SetAnimationSpeed(const float Speed)
{
    AnimatedSprite.SetAnimationSpeed(Speed);
}

void Sprite::AddAnimationFrame(const sf::IntRect &Frame)
{
    AnimatedSprite.AddAnimationFrame(Frame);
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
