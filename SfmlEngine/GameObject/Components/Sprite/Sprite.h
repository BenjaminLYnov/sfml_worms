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
    Sprite(const std::string &imagePath);

    // Implémentation de la méthode Start (héritée de Component).
    virtual void Start() override;

    // Implémentation de la méthode Update (héritée de Component).
    virtual void Update(float deltaTime) override;

    // Méthode pour définir la position du sprite.
    void SetPosition(const sf::Vector2f &newPosition);

    // Méthode pour obtenir la position du sprite.
    sf::Vector2f GetPosition() const;

    // Dessiner le sprite sur une fenêtre SFML.
    virtual void Render(sf::RenderWindow& Window) override;


private:
    std::unique_ptr<sf::Texture> texture; // std::unique_ptr pour sf::Texture
    std::unique_ptr<sf::Sprite> sprite;   // std::unique_ptr pour sf::Sprite
};
