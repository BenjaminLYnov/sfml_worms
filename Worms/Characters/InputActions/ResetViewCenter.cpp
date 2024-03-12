#include "ResetViewCenter.h"
#include "GameObject/Components/Input/InputAction/ActionKey.h"

ResetViewCenter::ResetViewCenter()
{
    AddKey(Key::Keyboard::R);
    AddKey(Key::Joystick::RStick);

}