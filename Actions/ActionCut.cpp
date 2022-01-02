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
	pManager->CloneComponent(); // clone selected componenet
	pManager->deleteSelected(); // delete selected component

	pUI->PrintMsg("Component Cutted");
}

void ActionCut::Undo()
{}

void ActionCut::Redo()
{}

