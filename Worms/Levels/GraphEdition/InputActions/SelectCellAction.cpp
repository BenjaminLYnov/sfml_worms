#include "SelectCellAction.h"
#include "GameObject/Components/Input/InputAction/ActionKey.h"

SelectCellAction::SelectCellAction()
{
    AddKey(Key::Mouse::Left);
}