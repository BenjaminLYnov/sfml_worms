#pragma once

#include "./../IComponent.h"
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML
#include <string>
#include <memory> // Incluez l'en-tête pour std::shared_ptr
#include <SFML/Graphics/Rect.hpp>

class AnimatedSprite;

namespace sf
{
    class Texture; // Forward declaration pour sf::Texture
    class Sprite;  // Forward declaration pour sf::Sprite
}

class Sprite : public IComponent
{
public:
    // Constructeur qui prend le chemin du fichier image pour le sprite.
    Sprite();

    // Implémentation de la méthode Start (héritée de Component).
    virtual void Start() override;

    // Implémentation de la méthode Update (héritée de Component).
    virtual void Update(const float DeltaTime) override;

    virtual void UpdatePosition() override;

    // Chargez la texture depuis la memoire
    bool LoadTextureFromMemory(const unsigned char *Data = nullptr, size_t Size = 0);

    void SetAnimationSpeed(const float Speed);
    void AddAnimationFrame(const sf::IntRect &Frame);
    void SetOriginToCenter();
    void ResetAnimation();
    void SetScale(const sf::Vector2f Scale);

    // Méthode pour définir la position du sprite.
    void SetOffset(const sf::Vector2f &NewPosition);

    // Méthode pour obtenir la position du sprite.
    sf::Vector2f GetPosition() const;

    // Dessiner le sprite sur une fenêtre SFML.
    virtual void Render(sf::RenderWindow &Window) override;

    std::shared_ptr<AnimatedSprite> Animation;

protected:
    sf::Vector2f Offset;

    std::shared_ptr<sf::Texture> Texture;   // std::shared_ptr pour sf::Texture
    std::shared_ptr<sf::Sprite> SfmlSprite; // std::shared_ptr pour sf::Sprite
};
