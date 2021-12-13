#include "ActionSave.h"
#include "..\ApplicationManager.h"

ActionSave::ActionSave(ApplicationManager* pApp) :Action(pApp)
{
}

ActionSave::~ActionSave(void)
{
}

void ActionSave::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//save circut
	pManager->SaveCircuit();

	//Print Action Message
	pUI->PrintMsg("Circuit Saved");
}

void ActionSave::Undo()
{}

void ActionSave::Redo()
{}