#include "ActionEditValue.h"
#include "../ApplicationManager.h"
#include "../Components/Component.h"
#include "../Actions/ActionAddMenu.h"
#include <string>

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

		this->SaveComponentParameters(pManager->getSelectedComponentId(), CompList[pManager->getSelectedComponentId()]->getValue());

		CompList[pManager->getSelectedComponentId()]->setValue(stod(newValue)); // Set the input value to the current selected component

		pUI->ClearStatusBar();
		pUI->PrintMsg("New Value Recorded!");

		// Initializing the pointer to the ActionAddMenu
		ActionAddMenu* Menu = new ActionAddMenu(pManager);
		Menu->DrawComponentMenu(CompList[pManager->getSelectedComponentId()]); // Redraw the edit menu for the current selected component

		delete Menu;
		Menu = nullptr;
	}
	else {
		pUI->ClearStatusBar();
		pUI->PrintMsg("Invalid Value Input!");
	}
}


// Saving the action parameters to be retireved in the undo/redo cases

void ActionEditValue::SaveComponentParameters(int SelectedItemId, double preVal) {
	this->targetComponent = SelectedItemId;
	this->previousValue = preVal;
}


void ActionEditValue::Undo()
{
	// Check if The Edit Action is applied to a Component
	if (targetComponent >= 0) {
		Component* CompList[200];
		pManager->GetComponentList(CompList);
		double temp_previousValue = CompList[this->targetComponent]->getValue(); // Save the current component's value in a temp variable
		CompList[this->targetComponent]->setValue(this->previousValue);
		this->previousValue = temp_previousValue; // Replace the previous value with the temporary one
	}
}

void ActionEditValue::Redo()
{
	this->Undo();
}
