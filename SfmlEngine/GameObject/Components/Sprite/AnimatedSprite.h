#pragma once

// Inclusion nécessaire pour utiliser sf::Vector2f et sf::IntRect : type de template spécialisé de la SFML
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <memory>
#include <vector>

namespace sf
{
    class Sprite;
}

class AnimatedSprite
{
public:
    AnimatedSprite();

    void SetSprite(std::shared_ptr<sf::Sprite> SfmlSpriteToAssign);
    void SetAnimationSpeed(const float Speed);
    void AddAnimationFrame(const sf::IntRect &Frame);
    void ResetFrames();
    void RestartAnimation();
    void PlayAnimation();
    void PauseAnimation();
    void SetFrameAt(const int IndexFrame);
    void SetStopAtLastFrame(const bool bStop); 

    void Update(const float DeltaTime);
    std::shared_ptr<sf::Sprite> GetSprite();

private:
    std::shared_ptr<sf::Sprite> SfmlSprite;
    std::vector<sf::IntRect> Frames;
    float FrameTime;
    float ElapsedTime;
    int CurrentFrame;

    bool bPlayAnimation = true;
    bool bStopAtLastFrame = false;
};
