#include "ActionExit.h"
#include "../ApplicationManager.h"

ActionExit::ActionExit(ApplicationManager* pApp) : Action(pApp)
{
}


ActionExit::~ActionExit(void)
{

}

void ActionExit::Execute() {
	pManager->SaveCircuit();
}

void ActionExit::Undo()
{}

void ActionExit::Redo()
{}
