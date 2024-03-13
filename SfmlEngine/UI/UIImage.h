#pragma once
#include "UIElement.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace sf
{
    class Sprite;
    class Texture;
}

class UIImage : public UIElement
{
public:
    UIImage(const unsigned char *Data, size_t Size, const Vec2f& _pos, const Vec2f& _size, const sf::Color& _color = sf::Color::White);
    virtual const sf::FloatRect& UpdateRect(const sf::FloatRect& _parentRect);
    virtual void InitResources() override;
    virtual void Draw(sf::RenderWindow& _window) override;
    virtual void SetVisibility(bool _vis) override;
    virtual void SetGreyed(bool _greyed) override;

    void SetColor(const sf::Color& _color);
    //void SetUv(const Vec2f& _start, const Vec2f& _end);

protected:

    sf::Color storedColor;
    sf::Color color;
    std::shared_ptr<sf::Sprite> sprite;
    std::shared_ptr<sf::Texture> texture;
    
};
