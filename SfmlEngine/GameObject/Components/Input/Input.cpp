#include "Input.h"
#include "InputAction/InputAction.h"
#include "TriggerEvent.h"

Input::Input()
{
}

void Input::Start()
{
}

void Input::Update(const float DeltaTime)
{
}

void Input::PollActionsEvents()
{
    for (const auto IA : InputActions)
        IA->PollKeyEvents();
}

void Input::SetNeedKeyReleaseFirst(const bool bNeedKeyReleaseFirst)
{
    for (const auto IA : InputActions)
        IA->SetNeedKeyReleaseFirst(bNeedKeyReleaseFirst);
}

// PROTECTED

void Input::AddInputAction(std::shared_ptr<InputAction> &NewIA)
{
    for (const auto IA : InputActions)
        if (IA == NewIA)
            return;
    InputActions.push_back(NewIA);
}
