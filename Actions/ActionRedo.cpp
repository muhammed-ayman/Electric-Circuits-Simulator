#include "ActionRedo.h"
#include "../ApplicationManager.h"
#include<windows.h>

ActionRedo::ActionRedo(ApplicationManager* pApp) : Action(pApp)
{
}


ActionRedo::~ActionRedo(void)
{

}

void ActionRedo::Execute() {
	pManager->Redo();
}

void ActionRedo::Undo()
{
	return;
}

void ActionRedo::Redo()
{
	return;
}
