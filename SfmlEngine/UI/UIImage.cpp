#include "UIImage.h"

UIImage::UIImage(const std::string& _url, const Vec2f& _pos, const Vec2f& _size, const sf::Color& _color)
    : UIElement(_pos, _size), color(_color), url(_url)
{
}

void UIImage::InitResources()
{
    UIElement::InitResources();

    texture.loadFromFile(url);
    sprite.setTexture(texture);
    SetColor(color);
}

void UIImage::SetColor(const sf::Color& _color)
{
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