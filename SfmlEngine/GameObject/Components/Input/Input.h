#pragma once

#include <memory>
#include <vector>
#include "./../IComponent.h"
#include "Callback.h"

class InputAction;
enum class ETriggerEvent;

class Input : public IComponent
{
public:
    Input();

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;

    virtual void PollActionsEvents();

    // Template pour accepter n'importe quel type de classe et méthode membre
    template <typename T, typename Method>
    void BindAction(std::shared_ptr<InputAction> &IA, ETriggerEvent TriggerEvent, T *Obj, Method MethodToBind);

protected:
    void AddInputAction(std::shared_ptr<InputAction> &NewIA);

private:
    std::vector<std::shared_ptr<InputAction>> InputActions;
};

#include "Input.tpp" // Inclure les définitions de template
