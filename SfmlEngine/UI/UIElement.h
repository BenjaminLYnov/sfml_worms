#pragma once

#include "SFML/Graphics.hpp"

using Vec2f = sf::Vector2f;

enum class UILayout
{
    None,
    List
};

enum class UIDirection
{
    Horizontal,
    Vertical
};

enum class UIAlignment
{
    None,
    Start,
    Center,
    End
};

class UIElement
{
protected:
    Vec2f pos;
    Vec2f size;

    sf::FloatRect renderRect;
    std::vector<UIElement*> childrenList;

    UILayout layout = UILayout::None;
    UIDirection direction = UIDirection::Horizontal;
    UIAlignment horizontal = UIAlignment::None;
    UIAlignment vertical = UIAlignment::None;

    void UpdateLayoutList();

public:

    bool drawDebug = false;

    UIElement(const Vec2f& _pos, const Vec2f& _size);
    ~UIElement();

    const Vec2f GetPos() const { return pos; }
    const Vec2f GetSize() const { return size; }

    void SetPosX(float x) { pos.x = x; }
    void SetPosY(float y) { pos.y = y; }

    void SetSize(const Vec2f& _size) { size = _size; }

    UILayout GetLayout() const { return layout; }
    UIDirection GetDirection() const { return direction; }

    void SetLayout(UILayout _layout, UIDirection _direction){ layout = _layout; direction = _direction; }
    void SetHorizontalAlignment(UIAlignment _align) { horizontal = _align; }
    void SetVerticalAlignment(UIAlignment _align) { vertical = _align; }

    UIAlignment GetHorizontalAlignment() const { return horizontal; }
    UIAlignment GetVerticalAlignment() const { return vertical; }

    float GetTotalChildrenWidth();
    float GetTotalChildrenHeight();

    template <typename T> T* AddChild(T* pChild)
    {
        if (std::find(childrenList.begin(), childrenList.end(), pChild) == childrenList.end())
        {
            childrenList.push_back(pChild);
            return pChild;
        }
        return nullptr;
    }

    void RemoveChild(UIElement* pChild);
    virtual void InitResources();
    virtual const sf::FloatRect& UpdateRect(const sf::FloatRect& parentRect);
    virtual void Update(float dTime);
    virtual void Draw(sf::RenderWindow& window);

    sf::RectangleShape debugRectangle;
};
