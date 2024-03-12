#include "LoadPartyAction.h"
#include "GameObject/Components/Input/InputAction/ActionKey.h"

LoadPartyAction::LoadPartyAction()
{
    AddKey(Key::Keyboard::L);
    AddKey(Key::Joystick::Start);
}