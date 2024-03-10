#include "MoveViewportAction.h"
#include "GameObject/Components/Input/InputAction/ActionKey.h"

MoveViewportAction::MoveViewportAction()
{
    AddKey(Key::Keyboard::D, true, Axis::Horizontal, false);
    AddKey(Key::Keyboard::Q, true, Axis::Horizontal, true);
    AddKey(Key::Keyboard::Z, true, Axis::Vertical, false);
    AddKey(Key::Keyboard::S, true, Axis::Vertical, true);

    // AddKey(Key::Keyboard::Right, true, Axis::Horizontal, false);
    // AddKey(Key::Keyboard::Left, true, Axis::Horizontal, true);

    AddKey(Key::Joystick::LStickAxis);
}
