#include "ActionSimWindow.h"
#include "ApplicationManager.h"

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
