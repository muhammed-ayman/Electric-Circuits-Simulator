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
	Component* CompList[MaxCompCount];
	pManager->GetComponentList(CompList);
	if (pManager->GetComponentCount() == 0) pUI->PrintMsg("No Components to delete!");
	else {
		for (int i = 0; i < pManager->GetComponentCount(); i++) {
			if (!CompList[i]->isCompClicked()) { ctr++; }
			else { ctrDeleted++; }
		}
		if ((ctr == pManager->GetComponentCount()) && (ctrDeleted == 0) && (pManager->GetComponentCount()) != 0) { pUI->PrintMsg("No Selected Components!"); }
		else if (ctrDeleted == 1)  pManager->deleteSelectedComponent();
		else pManager->deleteSelectedComponents(ctrDeleted);
		}

	}

void ActionDelete::Undo()
{}

void ActionDelete::Redo()
{}