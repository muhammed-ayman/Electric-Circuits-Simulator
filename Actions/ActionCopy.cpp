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

	if (!pUI->getWriteMode()) {
		pUI->PrintMsg("You can not perform this action");
		return;
	}

	pManager->CloneSelectedComponent(); // Clone the current selected component to the temporary component variable

	pUI->PrintMsg("Component Copied");
}

void ActionCopy::Undo()
{}

void ActionCopy::Redo()
{}

