#include "ActionDelete.h"
#include "..\ApplicationManager.h"

ActionDelete::ActionDelete(ApplicationManager* pApp) : Action(pApp)
{
}

ActionDelete::~ActionDelete(void)
{
}

void ActionDelete::Execute()
{

	//Get a Pointer to the user Interfaces
	int ctr = 0;
	int ctrDeleted = 0;
	UI* pUI = pManager->GetUI();
	if (pManager->GetComponentCount() == 0)pUI->PrintMsg("No Components to delete!"); // checks if there are no components
	else if (pManager->getSelectedComponentId() == -1) pUI->PrintMsg("No Selected Components!"); // if there are components but all are unselected
	else { // else, delete all selected components
		pManager->deleteSelectedComponent();
		pUI->PrintMsg("Deleted selected components!");
	}

	// TODO: check for connection selection
}

void ActionDelete::Undo()
{}

void ActionDelete::Redo()
{}