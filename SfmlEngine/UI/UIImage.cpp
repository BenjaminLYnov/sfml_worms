#include "UIImage.h"

UIImage::UIImage(const unsigned char *Data, size_t Size, const Vec2f& _pos, const Vec2f& _size, const sf::Color& _color)
    : UIElement(_pos, _size), color(_color)
{
    if (!Data && Size == 0)
        return;

    if (!texture.loadFromMemory(Data, Size))
        return;
}

void UIImage::InitResources()
{
    UIElement::InitResources();
    sprite.setTexture(texture);
    SetColor(color);
    storedColor = color;
}

void UIImage::SetColor(const sf::Color& _color)
{
    storedColor = color;
    color = _color;
    sprite.setColor(color);
}

/*void UIImage::SetUv(const Vec2f& _start, const Vec2f& _end)
{
    sf::IntRect rect;
    rect.left = _start.x * texture.getSize().x;
    rect.top = _start.y * texture.getSize().y;
    rect.width = (_end.x - _start.x) * texture.getSize().x;
    rect.height = (_end.y - _start.y) * texture.getSize().y;

    sprite.setTextureRect(rect);
}*/

const sf::FloatRect& UIImage::UpdateRect(const sf::FloatRect& _parentRect)
{
    const sf::FloatRect& rect = UIElement::UpdateRect(_parentRect);

    sprite.setPosition(rect.left, rect.top);
    sprite.setScale(rect.width / texture.getSize().x, rect.height / texture.getSize().y);
    return rect;
}

void UIImage::Draw(sf::RenderWindow& _window)
{
    _window.draw(sprite);
    UIElement::Draw(_window);
}

void UIImage::SetVisibility(bool _vis)
{
    UIElement::SetVisibility(_vis);
    SetColor(_vis ? storedColor : sf::Color::Transparent);
}

void UIImage::SetGreyed(bool _greyed)
{
    UIElement::SetGreyed(_greyed);
    SetColor(_greyed ? sf::Color(100, 100, 100) : storedColor);
}
