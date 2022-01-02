#include "ActionCopy.h"
#include "../ApplicationManager.h"

ActionCopy::ActionCopy(ApplicationManager* pApp) :Action(pApp)
{
}

ActionCopy::~ActionCopy(void)
{
}

void ActionCopy::Execute()
{

	// Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	pManager->CloneComponent();

	pUI->PrintMsg("Component Copied");
}

void ActionCopy::Undo()
{}

void ActionCopy::Redo()
{}

