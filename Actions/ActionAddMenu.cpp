#include "ActionAddMenu.h"

void ActionAddMenu::DrawComponentMenu(Component* Comp) {

	UI* pUI = pManager->GetUI();

	pUI->PrintMsg(Comp->getLabel());
	pUI->DrawEditMenu();

}

ActionAddMenu::~ActionAddMenu() {

}