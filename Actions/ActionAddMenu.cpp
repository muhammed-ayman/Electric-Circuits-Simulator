#include "ActionAddMenu.h"

void ActionAddMenu::DrawComponentMenu() {
	UI* pUI = pManager->GetUI();

	pUI->DrawEditMenu();

}

ActionAddMenu::~ActionAddMenu() {

}