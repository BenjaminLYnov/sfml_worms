#pragma once

// Inclusion nécessaire pour utiliser sf::Vector2f et sf::IntRect, un type de template spécialisé de la SFML
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <memory>
#include <vector>

namespace sf
{
    class Sprite;  
}

class AnimatedSprite {
public:
    AnimatedSprite();

    void SetSprite(std::shared_ptr<sf::Sprite> SfmlSpriteToAssign);
    void SetAnimationSpeed(const float Speed);
    void AddAnimationFrame(const sf::IntRect& Frame);

    void Update(const float DeltaTime);
    std::shared_ptr<sf::Sprite> GetSprite();

private:
    std::shared_ptr<sf::Sprite> SfmlSprite;
    std::vector<sf::IntRect> Frames;
    float FrameTime;
    float ElapsedTime;
    size_t CurrentFrame;
};
