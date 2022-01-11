#include "ActionDelete.h"
#include "..\ApplicationManager.h"

ActionDelete::ActionDelete(ApplicationManager* pApp) : Action(pApp)
{
}

void ActionDelete::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	if (pManager->GetComponentCount() == 0)
		pUI->PrintMsg("No Components to delete!"); // checks if there are no components
	
	else if (pManager->getSelectedComponentId() == -1) 
		pUI->PrintMsg("No Selected Components!"); // if there are components but all are unselected
	
	else { // else, delete all selected components
		Component* CompList[MaxCompCount];
		pManager->GetComponentList(CompList);
		for (int i = 0; i < MaxCompCount; i++) {
			if (CompList[i] == nullptr) {
				break;
			}
			if (CompList[i]->isClicked()) {
				this->SaveComponentParameters(CompList[i]);
				pManager->MakeCompNull(CompList[i]);
			}
		}
		pUI->PrintMsg("Deleted selected components!");
	}
}

void ActionDelete::SaveComponentParameters(Component* Comp) {
	this->targetComponentsUndo.push(Comp);
	this->deletedComponentUndoCounter++;
}

void ActionDelete::Undo()
{
	for (int i = 0; i < this->deletedComponentUndoCounter; i++) {
		pManager->AddComponent(this->targetComponentsUndo.top());
		this->targetComponentsRedo.push(this->targetComponentsUndo.top());
		this->targetComponentsUndo.pop();
	}
	swap(this->deletedComponentRedoCounter, this->deletedComponentUndoCounter);
}

void ActionDelete::Redo()
{
	for (int i = 0; i < this->deletedComponentRedoCounter; i++) {
		pManager->MakeCompNull(this->targetComponentsRedo.top());
		this->targetComponentsUndo.push(this->targetComponentsRedo.top());
		this->targetComponentsRedo.pop();
	}
	swap(this->deletedComponentRedoCounter, this->deletedComponentUndoCounter);
}

ActionDelete::~ActionDelete() {
	// Deleting Dynamic Objects of type Component
	while (!this->targetComponentsRedo.empty()) delete targetComponentsRedo.top(), targetComponentsRedo.pop(); // Clearing the Redo Stack Objects from memory
	while (!this->targetComponentsUndo.empty()) delete targetComponentsUndo.top(), targetComponentsUndo.pop(); // Clearing the Undo Stack Objects from memory
}