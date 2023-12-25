#pragma once

#include <memory>
#include <vector>
#include <functional>
#include "./../IComponent.h"

class InputAction;
enum class ETriggerEvent;

class Input : public IComponent
{
public:
    using Callback = std::function<void()>;

    Input();

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;

    void BindAction(InputAction &IA, ETriggerEvent TriggerEvent, const Callback &Callback);

private:

};
