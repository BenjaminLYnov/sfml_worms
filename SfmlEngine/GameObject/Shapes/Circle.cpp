#include "Circle.h"

Circle::Circle() : GameObject()
{
    SetName("Circle");
}

void Circle::Start()
{
    GameObject::Start();
}

void Circle::Update(const float DeltaTime)
{
    GameObject::Update(DeltaTime);
}
