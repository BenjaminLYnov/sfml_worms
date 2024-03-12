#include "AnimatedSprite.h"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

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
    if (!SfmlSprite)
        return;
        
    Frames.push_back(Frame);

    if (Frames.size() == 1)
        SfmlSprite->setTextureRect(Frames[0]);
}

void AnimatedSprite::Update(const float DeltaTime)
{
    if (!SfmlSprite || Frames.empty())
        return;

    if (!bPlayAnimation)
        return;

    if (bStopAtLastFrame)
    {
        if (IsOnLastFrame())
            return;
    }

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

void AnimatedSprite::ResetFrames()
{
    Frames.clear();
}

void AnimatedSprite::RestartAnimation()
{
    CurrentFrame = 0;
}

void AnimatedSprite::PlayAnimation()
{
    bPlayAnimation = true;
}

void AnimatedSprite::PauseAnimation()
{
    bPlayAnimation = false;
}

void AnimatedSprite::SetFrameAt(const int IndexFrame)
{
    if (!SfmlSprite)
        return;

    if (IndexFrame < 0)
        return;

    if (IndexFrame >= Frames.size())
        return;

    PauseAnimation();

    SfmlSprite->setTextureRect(Frames[IndexFrame]);
}

void AnimatedSprite::SetStopAtLastFrame(const bool bStop)
{
    bStopAtLastFrame = bStop;
}

bool AnimatedSprite::IsOnLastFrame() const
{
    return CurrentFrame == Frames.size() - 1;
}
