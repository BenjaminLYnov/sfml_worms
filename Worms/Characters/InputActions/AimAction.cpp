#include "AimAction.h"
#include "GameObject/Components/Input/InputAction/ActionKey.h"

AimAction::AimAction()
{
    AddKey(Key::Keyboard::Z, true, Axis::Vertical, false);
    AddKey(Key::Keyboard::S, true, Axis::Vertical, true);

    AddKey(Key::Keyboard::Up, true, Axis::Vertical, false);
    AddKey(Key::Keyboard::Down, true, Axis::Vertical, true);

    AddKey(Key::Joystick::LStickAxis);
}