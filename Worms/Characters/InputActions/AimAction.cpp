#include "AimAction.h"
#include "GameObject/Components/Input/InputAction/ActionKey.h"

AimAction::AimAction()
{
    AddKey(Key::Keyboard::Z, true, Axis::Vertical, false);
    AddKey(Key::Keyboard::S, true, Axis::Vertical, true);

    AddKey(Key::Joystick::L2, true, Axis::Vertical, false);
    AddKey(Key::Joystick::R2, true, Axis::Vertical, true);

}