#include "GraphMoveViewportAction.h"
#include "GameObject/Components/Input/InputAction/ActionKey.h"

GraphMoveViewportAction::GraphMoveViewportAction()
{
    AddKey(Key::Keyboard::D, true, Axis::Horizontal, false);
    AddKey(Key::Keyboard::Q, true, Axis::Horizontal, true);
    AddKey(Key::Keyboard::Z, true, Axis::Vertical, false);
    AddKey(Key::Keyboard::S, true, Axis::Vertical, true);
    AddKey(Key::Joystick::LStickAxis);
}
