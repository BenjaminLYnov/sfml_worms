#pragma once

#include "Key/Key.h"
#include <map>
#include "Axis.h"


class ActionKey
{
public:
   // Constructeurs pour initialiser chaque type de touche
    ActionKey(Key::Keyboard Key);
    ActionKey(Key::Mouse Button);
    ActionKey(Key::Joystick Button);
    // ActionKey(unsigned int JoystickId, Key::Joystick Button);

    void SetAxisType(const Axis AxisTypeToSet);
    void SetNegateFlag(const bool bNegateFlagToSet);
    
    enum class KeyType
    {
        Keyboard,
        Mouse,
        Joystick
    };

    KeyType KeyType;

    Axis AxisType;
    bool bIsAxisKey = false;
    bool bNegateFlag = false;

    union
    {
        Key::Keyboard KeyboardKey;
        Key::Mouse MouseButton;
        Key::Joystick JoystickButton; // Pair<JoystickId, Button>
        // std::pair<unsigned int, Key::Joystick> JoystickButton; // Pair<JoystickId, Button>
    };
};
