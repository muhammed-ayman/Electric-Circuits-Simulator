#include "ActionSimWindow.h"
#include "..\ApplicationManager.h"

ActionSimWindow::ActionSimWindow(ApplicationManager* pApp) :Action(pApp)
{
}

ActionSimWindow::~ActionSimWindow(void)
{
}

bool ActionSimWindow::Validate() {
	int counter = 0;
	Component* CompList[200];
	pManager->GetComponentList(CompList);
	if (pManager->GetGroundCount() == 1 && (pManager->GetComponentCount() == pManager->GetConnectionCount())) {
		for (int i = 0; i < pManager->GetComponentCount(); i++) {
			if (CompList[i] != nullptr) {
				if (pManager->getCompValue(CompList[i]) != 0.0) counter++;
			}
		}
		if (counter == pManager->GetComponentCount()) return true;
		else return false;
	}
	return false;
}

void ActionSimWindow::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	if (Validate()) {
		// unselecting selected objects in simulation mode
		Component* CompList[200];
		pManager->GetComponentList(CompList);
		for (int i = 0; i < 200; i++) {
			if (CompList[i] != nullptr) {
				CompList[i]->setClick(false);
			}
		}
		//creating simulation toolbar
		pUI->CreateSimulationToolBar();
		pUI->CreateDrawingArea();
		//Print Action Message
		pUI->PrintMsg("Simulation Mode Initialized");
	}
	else pUI->PrintMsg("Circuit is not valid! Make sure there is only one circuit, one ground, and full connections & values for each component!");
}

void ActionSimWindow::Undo()
{
}

void ActionSimWindow::Redo()
{
}
