#include "ActionKey.h"

ActionKey::ActionKey(Key::Keyboard Key) : KeyType(KeyType::Keyboard), KeyboardKey(Key) {}
ActionKey::ActionKey(Key::Mouse Button) : KeyType(KeyType::Mouse), MouseButton(Button) {}
ActionKey::ActionKey(Key::Joystick Button) : KeyType(KeyType::Joystick), JoystickButton(Button) {}
// ActionKey::ActionKey(unsigned int JoystickId, Key::Joystick Button) : KeyType(KeyType::Joystick), JoystickButton(JoystickId, Button) {}

void ActionKey::SetAxisType(const Axis AxisTypeToSet)
{
    AxisType = AxisTypeToSet;
}

void ActionKey::SetNegateFlag(const bool bNegateFlagToSet)
{
    bNegateFlag = bNegateFlagToSet;
}