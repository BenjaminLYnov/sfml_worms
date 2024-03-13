#include "Canvas.h"

#include "UIImage.h"

Canvas::Canvas(Vec2f _pos, Vec2f _size) : UIElement(_pos, _size)
{
}

void Canvas::InitResources()
{
    UIElement::InitResources();
}

const sf::FloatRect& Canvas::UpdateRect(const sf::FloatRect& _parentRect)
{
    const sf::FloatRect& ret = UIElement::UpdateRect(_parentRect);

    return ret;
}

void Canvas::Update(float dTime)
{
    UIElement::Update(dTime);
}

void Canvas::Draw(sf::RenderWindow& _window)
{
    UIElement::Draw(_window);
}
