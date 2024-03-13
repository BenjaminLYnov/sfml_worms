#pragma once

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML
#include <SFML/Graphics/Rect.hpp>

namespace sf
{
    class RenderWindow;
    class RectangleShape;
}

using Vec2f = sf::Vector2f;

class UIElement
{
protected:
    Vec2f pos;
    Vec2f size;

    sf::FloatRect renderRect;
    std::vector<std::shared_ptr<UIElement>> childrenList;

public:

    bool drawDebug;

    UIElement(const Vec2f& _pos, const Vec2f& _size);

    const Vec2f GetPos() const { return pos; }
    const Vec2f GetSize() const { return size; }

    void SetPosX(float x) { pos.x = x; }
    void SetPosY(float y) { pos.y = y; }

    void SetSize(const Vec2f& _size) { size = _size; }

    bool greyed;
    bool hidden;

    virtual void SetGreyed(bool _greyed){greyed = _greyed;}
    virtual void SetVisibility(bool _vis);

    float GetTotalChildrenWidth();
    float GetTotalChildrenHeight();

    std::shared_ptr<UIElement> AddChild(std::shared_ptr<UIElement> pChild);

    void RemoveChild(std::shared_ptr<UIElement> pChild);
    virtual void InitResources();
    virtual const sf::FloatRect& UpdateRect(const sf::FloatRect& parentRect);
    virtual void Update(float dTime);
    virtual void Draw(sf::RenderWindow& window);

    std::shared_ptr<sf::RectangleShape> debugRectangle;

    float initialRatio;
};
