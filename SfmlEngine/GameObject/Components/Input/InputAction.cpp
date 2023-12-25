#include "InputAction.h"
#include "TriggerEvent.h"
#include <iostream>

void InputAction::BindAction(ETriggerEvent TriggerEvent, const Callback &Callback)
{
    Callbacks[TriggerEvent].push_back(Callback);
}

void InputAction::PollKeyEvents()
{
    // On Started
    for (auto Key : Keys)
        if (sf::Keyboard::isKeyPressed(Key) && !bIsKeyPressed)
        {
            CallCallbacks(ETriggerEvent::STARTED);
            bIsKeyPressed = true;
            break;
        }

    // On Triggered
    for (auto Key : Keys)
        if (sf::Keyboard::isKeyPressed(Key))
        {
            CallCallbacks(ETriggerEvent::TRIGGERED);
            break;
        }

    // On Completed
    for (auto Key : Keys)
        if (!sf::Keyboard::isKeyPressed(Key) && bIsKeyPressed)
        {
            CallCallbacks(ETriggerEvent::COMPLETED);
            bIsKeyPressed = false;
            break;
        }
}

// PROTECTED

void InputAction::AddKey(sf::Keyboard::Key NewKey)
{
    for (const sf::Keyboard::Key Key : Keys)
        if (Key == NewKey)
            return;
    Keys.push_back(NewKey);
}

void InputAction::CallCallbacks(ETriggerEvent TriggerEvent)
{
    for (const auto Callback : Callbacks[TriggerEvent])
        Callback();
}
