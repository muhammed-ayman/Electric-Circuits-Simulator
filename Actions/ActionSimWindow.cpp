#include "ActionSimWindow.h"
#include "..\ApplicationManager.h"

ActionSimWindow::ActionSimWindow(ApplicationManager* pApp) :Action(pApp)
{
}

ActionSimWindow::~ActionSimWindow(void)
{
}

bool ActionSimWindow::Validate() {
	if (pManager->GetGroundCount() == 1 && (pManager->GetComponentCount() == pManager->GetConnectionCount())) return true;
	else return false;
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
	else pUI->PrintMsg("Circuit is not valid!");
}

void ActionSimWindow::Undo()
{
}

void ActionSimWindow::Redo()
{
}
