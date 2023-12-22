#include "Sprite.h"
#include <SFML/Graphics.hpp> // Incluez l'en-tête complet pour l'implémentation de la SFML

Sprite::Sprite(const std::string &imagePath)
{
    // Chargez la texture depuis le fichier image
    texture = std::make_unique<sf::Texture>();
    
    if (!texture->loadFromFile(imagePath))
    {
        // Gestion de l'erreur de chargement de la texture
        // Vous pouvez ajouter ici un code de gestion d'erreur approprié
    }

    // Initialisez le sprite avec la texture chargée
    sprite = std::make_unique<sf::Sprite>(*texture);

    // ... Autres initialisations de la classe Sprite
}

void Sprite::Start()
{
    // Code d'initialisation spécifique si nécessaire
}

void Sprite::Update(float deltaTime)
{
    // Code de mise à jour spécifique si nécessaire
}

void Sprite::SetPosition(const sf::Vector2f &newPosition)
{
    sprite->setPosition(newPosition);
}

sf::Vector2f Sprite::GetPosition() const
{
    return sprite->getPosition();
}

void Sprite::Render(sf::RenderWindow &Window)
{
    // Dessinez le sprite sur la fenêtre SFML
    Window.draw(*sprite);
}
