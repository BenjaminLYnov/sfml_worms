#pragma once
#include "UIElement.h"

class UIImage : public UIElement
{
public:
    UIImage(const std::string& _url, const Vec2f& _pos, const Vec2f& _size, const sf::Color& _color = sf::Color::White);
    virtual const sf::FloatRect& UpdateRect(const sf::FloatRect& _parentRect);
    virtual void InitResources() override;
    virtual void Draw(sf::RenderWindow& _window) override;

    void SetColor(const sf::Color& _color);
    void SetUv(const Vec2f& _start, const Vec2f& _end);

protected:

    sf::Color color;
    std::string url;
    sf::Sprite sprite;
    sf::Texture texture;
    
};
