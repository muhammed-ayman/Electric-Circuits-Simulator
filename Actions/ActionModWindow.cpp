#include "ActionModWindow.h"
#include "..\ApplicationManager.h"

ActionModWindow::ActionModWindow(ApplicationManager* pApp) :Action(pApp)
{
}

ActionModWindow::~ActionModWindow(void)
{
}

void ActionModWindow::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	pManager->CreateTemp();


	Component* TempCompList[MaxCompCount];
	pManager->GetTempComponentList(TempCompList);

	if (!TempCompList[pManager->getTempSelectedComponentId()]->getWriteMode()) {
		pUI->setWriteMode(false);
	}	

	//creating simulation toolbar

	pManager->UpdateInterface();
	pUI->ClearDrawingArea();
	pUI->CreateModuleToolBar();
	pUI->CreateDrawingArea();
	//Print Action Message
	pUI->PrintMsg("Module Mode Initialized");
}  

void ActionModWindow::Undo()
{
}

void ActionModWindow::Redo()
{
}
