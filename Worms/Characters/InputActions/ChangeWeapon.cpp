#include "ChangeWeaponAction.h"
#include "GameObject/Components/Input/InputAction/ActionKey.h"

ChangeWeaponAction::ChangeWeaponAction()
{
    AddKey(Key::Keyboard::R);
}
