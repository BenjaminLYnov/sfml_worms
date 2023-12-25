#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

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
