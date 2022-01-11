#include "ActionDeleteConnection.h"
#include "..\ApplicationManager.h"

ActionDelete::ActionDelete(ApplicationManager* pApp, Component* comp1, Component* comp2, int comp1Terminal, int comp2Terminal) : Action(pApp), SaveActionParameters(comp1, comp2, comp1Terminal, comp2Terminal)
{
}

void ActionDelete::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	
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