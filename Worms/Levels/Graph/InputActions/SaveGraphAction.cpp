#include "SaveGraphAction.h"
#include "GameObject/Components/Input/InputAction/ActionKey.h"

SaveGraphAction::SaveGraphAction()
{
    AddKey(Key::Keyboard::T);
    AddKey(Key::Joystick::RLeft);
}

