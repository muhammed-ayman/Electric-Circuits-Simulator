#include "ActionSimWindow.h"
#include "..\ApplicationManager.h"

ActionSimWindow::ActionSimWindow(ApplicationManager* pApp) :Action(pApp)
{
}

ActionSimWindow::~ActionSimWindow(void)
{
}

void ActionSimWindow::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
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
	//Print Action Message
	pUI->PrintMsg("Simulation Mode Initialized");
}

void ActionSimWindow::Undo()
{
}

void ActionSimWindow::Redo()
{
}
