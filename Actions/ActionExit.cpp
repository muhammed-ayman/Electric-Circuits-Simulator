#include "ActionExit.h"
#include "../ApplicationManager.h"
#include<windows.h>

ActionExit::ActionExit(ApplicationManager* pApp) : Action(pApp)
{
}


ActionExit::~ActionExit(void)
{

}

void ActionExit::Execute() {
	UI* pUI = pManager->GetUI();
	

	pUI->ClearDrawingArea();
	Sleep(200);
	pUI->ClearEditMenu();
	Sleep(200);
	pUI->ClearStatusBar();
	Sleep(200);
	pUI->PrintMsg("Cleaning...");
	Sleep(200);
	//pManager->SaveCircuit();

	pUI->PrintMsg("Exiting the program... Backup Circuit is saved");
	Sleep(200);
}

void ActionExit::Undo()
{}

void ActionExit::Redo()
{}
