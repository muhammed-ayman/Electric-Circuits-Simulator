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
	
	string newLabel = pUI->GetSrting(); // Get the new label input from the user

	// Initializing the pointer to the ActionAddMenu
	ActionAddMenu* Menu = new ActionAddMenu(pManager);

	if (pManager->getSelectedComponentId() >= 0) {

		Component* CompList[200];

		pManager->GetComponentList(CompList);

		CompList[pManager->getSelectedComponentId()]->setLabel(newLabel); // Set the input label value to the current selected component

		pUI->ClearStatusBar();
		pUI->PrintMsg("New Label Recorded!");

		Menu->DrawComponentMenu(CompList[pManager->getSelectedComponentId()]); // Redraw the edit menu for the current selected component

	}

	if (pManager->getSelectedConnectionId() >= 0) {

		Connection* ConnList[MaxConnCount];

		pManager->GetConnectionList(ConnList);

		ConnList[pManager->getSelectedConnectionId()]->setConnectionLabel(newLabel); // Set the input label value to the current selected connection

		pUI->ClearStatusBar();
		pUI->PrintMsg("New Label Recorded!");

		Menu->DrawConnectionMenu(ConnList[pManager->getSelectedConnectionId()]); // Redraw the edit menu for the current selected connection

	}

	delete Menu;
	Menu = nullptr;
}

void ActionEditLabel::Undo()
{}

void ActionEditLabel::Redo()
{}

