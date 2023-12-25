#include "InputAction.h"
#include "TriggerEvent.h"
#include <iostream>

void InputAction::AddAction(ETriggerEvent &TriggerEvent, const Callback &Callback)
{
    switch ((TriggerEvent))
    {
    case ETriggerEvent::STARTED:
        TEStart.push_back(Callback);
        break;
    case ETriggerEvent::COMPLETED:
        TECompleted.push_back(Callback);
        break;
    case ETriggerEvent::TRIGGERED:
        TETriggered.push_back(Callback);
        break;
    default:
        break;
    }
}

void InputAction::Update(const float DeltaTime)
{
    for (auto Key : Keys)
    {
        // if (sf::Keyboard::)
        // // if (sf::Keyboard::isKeyPressed(Key))
        // {
        //     std::cout << "toto\n";
        // }
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