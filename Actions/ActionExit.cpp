#include "ActionExit.h"
#include "../ApplicationManager.h"
#include<windows.h>

ActionExit::ActionExit(ApplicationManager* pApp) : Action(pApp)
{
	UI* pUI = pManager->GetUI();
	pUI->ClearDrawingArea();
	Sleep(1000);
	pUI->ClearEditMenu();
	Sleep(1000);
	pUI->ClearStatusBar();
	Sleep(1000);
	pUI->PrintMsg("Cleaning...");
	Sleep(1000);
}


ActionExit::~ActionExit(void)
{

}

void ActionExit::Execute() {
	UI* pUI = pManager->GetUI();
	
	pManager->SaveCircuit();

	pUI->PrintMsg("Exiting the program... Backup Circuit is saved");
	Sleep(1000);
}

void ActionExit::Undo()
{}

void ActionExit::Redo()
{}
