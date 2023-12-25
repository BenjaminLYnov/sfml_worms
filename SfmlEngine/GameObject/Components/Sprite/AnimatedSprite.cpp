#include "AnimatedSprite.h"
#include <SFML/Graphics/Sprite.hpp>

AnimatedSprite::AnimatedSprite() : FrameTime(0.1f), ElapsedTime(0.0f), CurrentFrame(0) {}

void AnimatedSprite::SetSprite(std::shared_ptr<sf::Sprite> SfmlSpriteToAssign)
{
    SfmlSprite = SfmlSpriteToAssign;
}

void AnimatedSprite::SetAnimationSpeed(const float Speed)
{
    FrameTime = Speed;
}

void AnimatedSprite::AddAnimationFrame(const sf::IntRect &Frame)
{
    Frames.push_back(Frame);

    if (Frames.size() == 1)
        SfmlSprite->setTextureRect(Frames[0]);
}

void AnimatedSprite::Update(const float DeltaTime)
{
    if (!SfmlSprite || Frames.empty())
        return;

    ElapsedTime += DeltaTime;
    if (ElapsedTime >= FrameTime)
    {
        ElapsedTime -= FrameTime;
        CurrentFrame = (CurrentFrame + 1) % Frames.size();
        SfmlSprite->setTextureRect(Frames[CurrentFrame]);
    }
}

std::shared_ptr<sf::Sprite> AnimatedSprite::GetSprite()
{

    return SfmlSprite;
}
