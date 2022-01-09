#include "ActionUndo.h"
#include "../ApplicationManager.h"
#include<windows.h>

ActionUndo::ActionUndo(ApplicationManager* pApp) : Action(pApp)
{
}


ActionUndo::~ActionUndo(void)
{

}

void ActionUndo::Execute() {
	pManager->Undo();
}

void ActionUndo::Undo()
{
	return;
}

void ActionUndo::Redo()
{
	return;
}
