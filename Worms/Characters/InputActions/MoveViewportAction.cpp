#include "MoveViewportAction.h"
#include "GameObject/Components/Input/InputAction/ActionKey.h"

MoveViewportAction::MoveViewportAction()
{
    AddKey(Key::Keyboard::Right, true, Axis::Horizontal, false);
    AddKey(Key::Keyboard::Left, true, Axis::Horizontal, true);
    AddKey(Key::Keyboard::Up, true, Axis::Vertical, false);
    AddKey(Key::Keyboard::Down, true, Axis::Vertical, true);
    AddKey(Key::Joystick::RStickAxis);
}
