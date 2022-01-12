#include "ActionAddDefault.h"
#include "../ApplicationManager.h"
#include "ActionLoad.h"

ActionAddDefault::ActionAddDefault(ApplicationManager* pApp) :Action(pApp)
{
}

ActionAddDefault::~ActionAddDefault(void)
{
}

void ActionAddDefault::Execute()
{
	// Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	if (!pUI->getWriteMode()) {
		pUI->PrintMsg("You can not perform this action");
		return;
	}

	Component* TempCompList[MaxCompCount];
	pManager->GetTempComponentList(TempCompList);
	TempCompList[pManager->getTempSelectedComponentId()]->setWriteMode(false);

	pUI->setWriteMode(false);
	


	Action* pAct = new ActionLoad(pManager);
	pAct->Execute();
	
	pUI->PrintMsg("Default added, you can only edit values");
}

void ActionAddDefault::Undo()
{}

void ActionAddDefault::Redo()
{}

