#include "InputAction.h"
#include "../TriggerEvent.h"
#include <iostream>
#include "Key/Key.h"
#include "ActionKey.h"
#include "Math/Vector/Vector.h"

void InputAction::BindAction(ETriggerEvent TriggerEvent, const InputCallback &Callback)
{
    Callbacks[TriggerEvent].push_back(Callback);
}

void InputAction::PollKeyEvents()
{
    const bool KeyPressed = KeyIsPressed();
    const sf::Vector2f InputValue = GetInputValue();

    // On Started
    if (KeyPressed && !bIsKeyPressed)
    {
        bIsKeyPressed = true;
        CallCallbacks(ETriggerEvent::Started, InputValue);
    }

    // On Triggered
    if (KeyPressed)
        CallCallbacks(ETriggerEvent::Triggered, InputValue);

    // On Completed
    if (!KeyPressed && bIsKeyPressed)
    {
        bIsKeyPressed = false;
        CallCallbacks(ETriggerEvent::Completed, InputValue);
    }
}

////////////////////////////////////////////////////
// PROTECTED

void InputAction::AddKey(ActionKey NewActionKey, const bool bIsAxisKey, const Axis AxisType, const bool bNegateFlag)
{
    if (!HasKey(NewActionKey))
    {
        if (bIsAxisKey)
        {
            NewActionKey.bIsAxisKey = true;
            NewActionKey.SetAxisType(AxisType);
            NewActionKey.SetNegateFlag(bNegateFlag);
        }
        ActionKeys.push_back(NewActionKey);
    }
}

////////////////////////////////////////////////////
// PRIVATE

void InputAction::CallCallbacks(ETriggerEvent TriggerEvent, const sf::Vector2f Value)
{
    for (const InputCallback Callback : Callbacks[TriggerEvent])
        Callback(Value);
}

sf::Vector2f InputAction::GetInputValue() const
{
    sf::Vector2f InputValue = sf::Vector2f(0, 0);

    for (const auto &ActionKey : ActionKeys)
    {
        switch (ActionKey.KeyType)
        {
        case ActionKey::KeyType::Keyboard:
            if (Key::IsKeyPressed(ActionKey.KeyboardKey))
                SetActionKeyValue(ActionKey, InputValue);
            break;
        case ActionKey::KeyType::Mouse:
            if (Key::IsKeyPressed(ActionKey.MouseButton))
                SetActionKeyValue(ActionKey, InputValue);
            break;
        case ActionKey::KeyType::Joystick:
            if (Key::IsKeyPressed(0, ActionKey.JoystickButton))
            {
                SetActionKeyValue(ActionKey, InputValue);
                break;
            }
            if (Key::KeyIsStickAxis(ActionKey.JoystickButton))
            {
                if (!Key::IsUsingStick(ActionKey.JoystickButton))
                    break;
                sf::Vector2f AxisValue = Key::GetAxisValue(ActionKey.JoystickButton);
                float Magnitude = Key::GetMagnitude(AxisValue);
                InputValue = AxisValue;
                Vector::Normalized(InputValue);
                InputValue *= Magnitude / 100;
                return InputValue;
            }
            break;
        }
    }

    Vector::Normalized(InputValue);
    return InputValue;
}

bool InputAction::KeyIsPressed() const
{
    for (const auto &ActionKey : ActionKeys)
    {
        switch (ActionKey.KeyType)
        {
        case ActionKey::KeyType::Keyboard:
            if (Key::IsKeyPressed(ActionKey.KeyboardKey))
                return true;
            break;
        case ActionKey::KeyType::Mouse:
            if (Key::IsKeyPressed(ActionKey.MouseButton))
                return true;
            break;
        case ActionKey::KeyType::Joystick:
            if (Key::IsKeyPressed(0, ActionKey.JoystickButton) || Key::IsUsingStick(ActionKey.JoystickButton))
                return true;
            break;
        }
    }
    return false;
}

bool InputAction::HasKey(const ActionKey &ActionKey) const
{
    for (const auto &ExistingKey : ActionKeys)
    {
        if (AreKeysEqual(ActionKey, ExistingKey))
        {
            return true;
        }
    }
    return false;
}

bool InputAction::AreKeysEqual(const ActionKey &Key1, const ActionKey &Key2) const
{
    if (Key1.KeyType != Key2.KeyType)
        return false;

    switch (Key1.KeyType)
    {
    case ActionKey::KeyType::Keyboard:
        return Key1.KeyboardKey == Key2.KeyboardKey;
    case ActionKey::KeyType::Mouse:
        return Key1.MouseButton == Key2.MouseButton;
    case ActionKey::KeyType::Joystick:
        return Key1.JoystickButton == Key2.JoystickButton;
    default:
        return false;
    }
}

void InputAction::SetActionKeyValue(const ActionKey &ActionKey, sf::Vector2f &InputValue) const
{
    if (!ActionKey.bIsAxisKey)
        return;

    switch (ActionKey.AxisType)
    {
    case Axis::Horizontal:
        InputValue.x = ActionKey.bNegateFlag ? -1 : 1;
        break;
    case Axis::Vertical:
        InputValue.y = ActionKey.bNegateFlag ? 1 : -1;
        break;
    }
}
