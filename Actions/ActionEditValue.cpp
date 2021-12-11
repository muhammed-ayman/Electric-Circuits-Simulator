#include "ActionEditValue.h"
#include "../ApplicationManager.h"
#include "../Components/Component.h"
#include "../Actions/ActionAddMenu.h"

ActionEditValue::ActionEditValue(ApplicationManager* pApp) :Action(pApp)
{
}

ActionEditValue::~ActionEditValue(void)
{
}

void ActionEditValue::Execute()
{

	// Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	pUI->PrintMsg("Type in the new Value & Press Enter when you finish");

	string newValue = pUI->GetSrting();

	bool canBeConverted = true;

	int points = 0;

	for (int i = 0; i < newValue.length(); i++) {
		if (newValue[i] == '.') {
			points++;
		} else if (newValue[i] > 57 || newValue[i] < 48) {
			canBeConverted = false;
			break;
		}
		if (points > 1) {
			canBeConverted = false;
			break;
		}
	}

	if (canBeConverted) {

		Component* CompList[200];

		pManager->GetComponentList(CompList);

		CompList[pManager->getSelectedComponentId()]->setValue(stod(newValue));

		pUI->ClearStatusBar();
		pUI->PrintMsg("New Value Recorded!");

		// Initializing the pointer to the ActionAddMenu
		ActionAddMenu* Menu = new ActionAddMenu(pManager);
		Menu->DrawComponentMenu(CompList[pManager->getSelectedComponentId()]);

		delete Menu;

	}
	else {
		pUI->ClearStatusBar();
		pUI->PrintMsg("Invalid Value Input!");
	}
}

void ActionEditValue::Undo()
{}

void ActionEditValue::Redo()
{}

