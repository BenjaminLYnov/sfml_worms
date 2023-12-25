#include "Input.h"
#include "InputAction.h"
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

void Input::BindAction(InputAction &IA, ETriggerEvent TriggerEvent, const Callback& Callback)
{
    IA.AddAction(TriggerEvent, Callback);
}
