#include "ActionCut.h"
#include "../ApplicationManager.h"

ActionCut::ActionCut(ApplicationManager* pApp) :Action(pApp)
{
}

ActionCut::~ActionCut(void)
{
}

void ActionCut::Execute()
{

	// Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	pManager->CloneSelectedComponent(); // Clone the selected componenet
	pManager->deleteSelectedComponent(); // Delete the selected component

	pUI->PrintMsg("Component Cut");
}

void ActionCut::Undo()
{}

void ActionCut::Redo()
{}

