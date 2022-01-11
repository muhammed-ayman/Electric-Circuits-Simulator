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

		this->SaveComponentParameters(pManager->getSelectedComponentId(), CompList[pManager->getSelectedComponentId()]->getLabel());

		CompList[pManager->getSelectedComponentId()]->setLabel(newLabel); // Set the input label value to the current selected component

		pUI->ClearStatusBar();
		pUI->PrintMsg("New Label Recorded!");

		Menu->DrawComponentMenu(CompList[pManager->getSelectedComponentId()]); // Redraw the edit menu for the current selected component

	}

	if (pManager->getSelectedConnectionId() >= 0) {

		Connection* ConnList[MaxConnCount];

		pManager->GetConnectionList(ConnList);

		this->SaveConnectionParameters(pManager->getSelectedConnectionId(), ConnList[pManager->getSelectedConnectionId()]->getConnectionLabel());

		ConnList[pManager->getSelectedConnectionId()]->setConnectionLabel(newLabel); // Set the input label value to the current selected connection

		pUI->ClearStatusBar();
		pUI->PrintMsg("New Label Recorded!");

		Menu->DrawConnectionMenu(ConnList[pManager->getSelectedConnectionId()]); // Redraw the edit menu for the current selected connection

	}

	delete Menu;
	Menu = nullptr;
}

// Saving the action parameters to be retireved in the undo/redo cases

void ActionEditLabel::SaveComponentParameters(int SelectedItemId, string preLabel) {
	this->targetComponent = SelectedItemId;
	this->previousLabel = preLabel;
}

void ActionEditLabel::SaveConnectionParameters(int SelectedItemId, string preLabel) {
	this->targetConnection = SelectedItemId;
	this->previousLabel = preLabel;
}


void ActionEditLabel::Undo()
{
	// Check if The Edit Action is applied to a Connection or a Component
	if (targetComponent >= 0) {
		Component* CompList[200];
		pManager->GetComponentList(CompList);
		string temp_previousLabel = CompList[this->targetComponent]->getLabel(); // Save the current component's label in a temp variable
		CompList[this->targetComponent]->setLabel(this->previousLabel);
		this->previousLabel = temp_previousLabel; // Replace the previous label with the temporary one
	}

	if (targetConnection >= 0) {
		Connection* ConnList[MaxConnCount];
		pManager->GetConnectionList(ConnList);
		string temp_previousLabel = ConnList[this->targetConnection]->getConnectionLabel(); // Save the current connection's label in a temp variable
		ConnList[this->targetConnection]->setConnectionLabel(this->previousLabel);
		this->previousLabel = temp_previousLabel; // Replace the previous label with the temporary one
	}

}

void ActionEditLabel::Redo()
{
	this->Undo();
}

