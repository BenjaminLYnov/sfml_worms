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
    
    virtual void PollActionsEvents();

    void BindAction(std::shared_ptr<InputAction> &IA, ETriggerEvent TriggerEvent, const Callback &Callback);

protected:
    void AddInputAction(std::shared_ptr<InputAction> &NewIA);

private:
    std::vector<std::shared_ptr<InputAction>> InputActions;

};
