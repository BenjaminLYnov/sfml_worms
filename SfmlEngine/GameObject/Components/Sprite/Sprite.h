#pragma once

#include "./../IComponent.h"
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML
#include <string>
#include <memory> // Incluez l'en-tête pour std::unique_ptr

namespace sf
{
    class Texture; // Forward declaration pour sf::Texture
    class Sprite;  // Forward declaration pour sf::Sprite
}

class Sprite : public IComponent
{
public:
    // Constructeur qui prend le chemin du fichier image pour le sprite.
    Sprite(const unsigned char *Data = nullptr, size_t Size = 0);

    // Implémentation de la méthode Start (héritée de Component).
    virtual void Start() override;

    // Implémentation de la méthode Update (héritée de Component).
    virtual void Update(float DeltaTime) override;

    bool LoadTextureFromMemory(const unsigned char *Data = nullptr, size_t Size = 0);

    // Méthode pour définir la position du sprite.
    void SetPosition(const sf::Vector2f &NewPosition);

    // Méthode pour obtenir la position du sprite.
    sf::Vector2f GetPosition() const;

    // Dessiner le sprite sur une fenêtre SFML.
    virtual void Render(sf::RenderWindow &Window) override;

private:
    std::unique_ptr<sf::Texture> Texture; // std::unique_ptr pour sf::Texture
    std::unique_ptr<sf::Sprite> SfmlSprite;   // std::unique_ptr pour sf::Sprite
};
