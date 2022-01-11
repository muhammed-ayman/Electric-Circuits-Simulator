#include "ActionMeausreCurrent.h"
#include "../ApplicationManager.h"


ActionMeasureCurrent::ActionMeasureCurrent(ApplicationManager* pApp) : Action(pApp)
{
	pManager->GetComponentList(CompList);
}

ActionMeasureCurrent::~ActionMeasureCurrent(void)
{
}

void ActionMeasureCurrent::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	pUI->PrintMsg("Select component to measure its current");

	int x = 0, y = 0;

	// Retrieves the mouse coordinates clicked by the user
	pUI->GetPointClicked(x, y);
	int compId = pManager->getComponent(x, y);
	if (compId == -1) {
		pUI->PrintMsg("Nothing selected!");
	}
	else {
		string compType = CompList[compId]->GetItemType();
		if (compType == "BAT") { pUI->PrintMsg("Cannot Measure Current at Battery"); }
		else if (compType == "GND") { pUI->PrintMsg("Cannot Measure Current at Ground"); }
		else {
			string expression = "";
			expression = "Current in " + CompList[compId]->getLabel() + " : " + to_string(pManager->getTotalCurrent());
			pUI->PrintMsg(expression);
		}

	}

}

void ActionMeasureCurrent::Undo()
{
}

void ActionMeasureCurrent::Redo()
{
}
