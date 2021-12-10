#include "ActionAddMenu.h"

void ActionAddMenu::DrawComponentMenu(Component* Comp) {

	UI* pUI = pManager->GetUI();	

	pUI->DrawEditMenu(Comp->getLabel(), to_string(Comp->getValue()));

}

ActionAddMenu::~ActionAddMenu() {

}