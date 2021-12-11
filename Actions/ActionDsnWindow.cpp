#include "ActionDsnWindow.h"
#include "..\ApplicationManager.h"

ActionDsnWindow::ActionDsnWindow(ApplicationManager* pApp) :Action(pApp)
{
}

ActionDsnWindow::~ActionDsnWindow(void)
{
}

void ActionDsnWindow::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	//creating simulation toolbar
	pUI->CreateDesignToolBar();
	//Print Action Message
	pUI->PrintMsg("Back to design mode");
}

void ActionDsnWindow::Undo()
{
}

void ActionDsnWindow::Redo()
{
}
