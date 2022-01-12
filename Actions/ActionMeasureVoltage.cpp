#include "ActionMeasureVoltage.h"
#include "../ApplicationManager.h"
#include "..\Components\Switch.h"
#include "..\Components\Buzzer.h"
#include "..\Components\Ground.h"
#include "..\Components\Battery.h"

ActionMeasureVoltage::ActionMeasureVoltage(ApplicationManager* pApp) : Action(pApp)
{
	pManager->GetComponentList(CompList);
}

ActionMeasureVoltage::~ActionMeasureVoltage(void)
{
}

void ActionMeasureVoltage::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	pUI->PrintMsg("Select component to measure its voltage");

	int x = 0, y = 0;

	// Retrieves the mouse coordinates clicked by the user
	pUI->GetPointClicked(x, y);
	int compId = pManager->getComponent(x, y);
	if (compId == -1) {
		pUI->PrintMsg("Nothing selected!");
	}
	else {
		string expression = "";

		Battery* bat = dynamic_cast<Battery*>(CompList[compId]);
		Ground* grd = dynamic_cast<Ground*>(CompList[compId]); 
		Switch* swt = dynamic_cast<Switch*>(CompList[compId]);

		if (bat != nullptr) {
			expression = "Voltage in " + CompList[compId]->getLabel() + " : " + to_string(CompList[compId]->getValue());

			pUI->PrintMsg(expression);
		}
		else if ((grd != nullptr) || (swt != nullptr)) {
			expression = "Voltage in " + CompList[compId]->getLabel() + " : " + to_string(0);
			pUI->PrintMsg(expression);
		}
		else {
			string expression = "";
			expression = "Voltage in " + CompList[compId]->getLabel() + " : " + to_string(CompList[compId]->getValue() * pManager->getTotalCurrent());
			pUI->PrintMsg(expression);
		}
		
	}
	}

	

void ActionMeasureVoltage::Undo()
{
}

void ActionMeasureVoltage::Redo()
{
}
