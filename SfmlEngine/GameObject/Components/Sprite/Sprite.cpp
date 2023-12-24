#include "Sprite.h"
#include <SFML/Graphics.hpp> // Incluez l'en-tête complet pour l'implémentation de la SFML
#include <iostream>

Sprite::Sprite(const unsigned char *Data, size_t Size)
{
    // Initialiser les instances
    Texture = std::make_unique<sf::Texture>();
    SfmlSprite = std::make_unique<sf::Sprite>();

    // Chargez la texture depuis la memoire
    if (Data && Size > 0)
        LoadTextureFromMemory(Data, Size);
}

void Sprite::Start()
{
    // Code d'initialisation spécifique si nécessaire
}

void Sprite::Update(float deltaTime)
{
    // Code de mise à jour spécifique si nécessaire
}

bool Sprite::LoadTextureFromMemory(const unsigned char *Data, size_t Size)
{
    if (Texture->loadFromMemory(Data, Size))
    {
        // Initialisez le sprite avec la texture chargée
        SfmlSprite = std::make_unique<sf::Sprite>(*Texture);
        return true; // Chargement réussi
    }
    // Gérer l'erreur si le chargement échoue
    return false;
}

void Sprite::SetPosition(const sf::Vector2f &NewPosition)
{
    if (!SfmlSprite)
        return;
    SfmlSprite->setPosition(NewPosition);
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
