#include "ZoomViewportAction.h"
#include "GameObject/Components/Input/InputAction/ActionKey.h"

ZoomViewportAction::ZoomViewportAction()
{
    AddKey(Key::Keyboard::A, true, Axis::Horizontal, false);
    AddKey(Key::Keyboard::E, true, Axis::Horizontal, true);

}
