#pragma once
#include "UIElement.h"

class Canvas : public UIElement
{
public:
    
    Canvas(Vec2f _pos, Vec2f _size);
    ~Canvas();

    void InitResources() override;

    virtual const sf::FloatRect& UpdateRect(const sf::FloatRect& _parentRect) override;
    virtual void Update(float dTime) override;
    virtual void Draw(sf::RenderWindow& _window) override;
    
};
