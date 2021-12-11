#include "ActionEditLabel.h"
#include "../ApplicationManager.h"
#include "../Components/Component.h"
#include "../Actions/ActionAddMenu.h"

ActionEditLabel::ActionEditLabel(ApplicationManager* pApp) :Action(pApp)
{
}


ActionEditLabel::~ActionEditLabel(void)
{
}

void ActionEditLabel::Execute()
{

	// Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	pUI->PrintMsg("Type in the new Label & Press Enter when you finish");
	
	string newLabel = pUI->GetSrting();

	Component* CompList[200];

	pManager->GetComponentList(CompList);

	CompList[pManager->getSelectedComponentId()]->setLabel(newLabel);

	pUI->ClearStatusBar();
	pUI->PrintMsg("New Label Recorded!");

	// Initializing the pointer to the ActionAddMenu
	ActionAddMenu* Menu = new ActionAddMenu(pManager);
	Menu->DrawComponentMenu(CompList[pManager->getSelectedComponentId()]);

	delete Menu;
}

void ActionEditLabel::Undo()
{}

void ActionEditLabel::Redo()
{}

