#include "UIElement.h"
#include <iostream>

UIElement::UIElement(const Vec2f& _pos, const Vec2f& _size) : pos(_pos), size(_size)
{
    initialRatio = _size.x / _size.y;
}

void UIElement::InitResources()
{
    drawDebug = false;
    debugRectangle.setOutlineColor(sf::Color::Red);
    debugRectangle.setOutlineThickness(1);
    debugRectangle.setFillColor(sf::Color::Transparent);

    for(std::shared_ptr<UIElement> child : childrenList)
        child->InitResources();
}

void UIElement::RemoveChild(std::shared_ptr<UIElement> child)
{
    auto found = std::find(childrenList.begin(), childrenList.end(), child);
    if(found != childrenList.end())
    {
        childrenList.erase(found);
    }
}

void UIElement::Update(float dTime)
{
    for(std::shared_ptr<UIElement> child : childrenList)
        child->Update(dTime);
}

const sf::FloatRect& UIElement::UpdateRect(const sf::FloatRect& parentRect)
{
    Vec2f vPos = Vec2f(parentRect.left, parentRect.top) + Vec2f(pos.x * parentRect.width, pos.y * parentRect.height);
    Vec2f vSize = Vec2f(parentRect.width * size.x, parentRect.height * size.y);
    

    renderRect.left = vPos.x;
    renderRect.top = vPos.y;

    renderRect.width = vSize.x;
    renderRect.height = vSize.y;

    if(drawDebug)
    {
        debugRectangle.setPosition(renderRect.left, renderRect.top);
        debugRectangle.setSize(sf::Vector2f(renderRect.width, renderRect.height));
    }

    for(std::shared_ptr<UIElement> child : childrenList)
        child->UpdateRect(renderRect);

    return renderRect;
}

void UIElement::SetVisibility(bool _vis)
{
    for (auto child : childrenList)
    {
        child->SetVisibility(_vis);
    }
}

float UIElement::GetTotalChildrenWidth()
{
    float totalWidth = 0;
    for(std::shared_ptr<UIElement> child : childrenList)
    {
        totalWidth += child->GetSize().x;
    }
    return totalWidth;
}

float UIElement::GetTotalChildrenHeight()
{
    float totalHeight = 0;
    for(std::shared_ptr<UIElement> child : childrenList)
    {
        totalHeight += child->GetSize().y;
    }
    return totalHeight;
}

std::shared_ptr<UIElement> UIElement::AddChild(std::shared_ptr<UIElement> pChild)
{
    if (std::find(childrenList.begin(), childrenList.end(), pChild) == childrenList.end())
    {
        childrenList.push_back(pChild);
        return pChild;
    }
    return nullptr;
}

void UIElement::Draw(sf::RenderWindow& window)
{
    if(drawDebug)
    {
        window.draw(debugRectangle);
    }
    for(std::shared_ptr<UIElement> child : childrenList)
        child->Draw(window);
}