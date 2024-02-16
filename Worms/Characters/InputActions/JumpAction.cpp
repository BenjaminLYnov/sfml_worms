#include "JumpAction.h"
#include "GameObject/Components/Input/InputAction/ActionKey.h"

JumpAction::JumpAction()
{
    AddKey(Key::Keyboard::M);
    AddKey(Key::Keyboard::Space);
}
