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

	string newValue = pUI->GetSrting(); // Get the value input from the user

	// Validate the newValue
	
	bool canBeConverted = true; // Can be converted to double

	int points = 0; // number of decimal points (shouldn't exceed one)

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

	// Proceed and change the value if it's a vaild double value
	if (canBeConverted) {

		Component* CompList[200];

		pManager->GetComponentList(CompList);

		CompList[pManager->getSelectedComponentId()]->setValue(stod(newValue)); // Set the input value to the current selected component

		pUI->ClearStatusBar();
		pUI->PrintMsg("New Value Recorded!");

		// Initializing the pointer to the ActionAddMenu
		ActionAddMenu* Menu = new ActionAddMenu(pManager);
		Menu->DrawComponentMenu(CompList[pManager->getSelectedComponentId()]); // Redraw the edit menu for the current selected component

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

