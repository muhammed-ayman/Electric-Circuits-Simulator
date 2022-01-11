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

	else if (pManager->getSelectedConnectionId() == -1 && pManager->getSelectedComponentId() == -1)
		pUI->PrintMsg("No Selected Items!");
	
	else { // else, delete all selected components & connections
		
		// Get the Component List, save the component parameters, and make it null
		Component* CompList[MaxCompCount];
		pManager->GetComponentList(CompList);
		for (int i = 0; i < MaxCompCount; i++) {
			if (CompList[i] == nullptr) {
				break;
			}
			if (CompList[i]->isClicked()) {
				this->SaveComponentParameters(CompList[i]);
				pManager->MakeCompNull(CompList[i]);
				if (CompList[i]->getTerm1Conn()) CompList[i]->getTerm1Conn()->setClick(true);
				if (CompList[i]->getTerm2Conn()) CompList[i]->getTerm2Conn()->setClick(true);
			}
		}

		// Get the Connection List, save the connection parameters, and make it null
		Connection* ConnList[MaxConnCount];
		pManager->GetConnectionList(ConnList);
		for (int i = 0; i < MaxConnCount; i++) {
			if (ConnList[i] == nullptr) {
				break;
			}
			if (ConnList[i]->isClicked()) {
				this->SaveConnectionParameters(ConnList[i]);
				pManager->MakeConnNull(ConnList[i]);
			}
		}

		pUI->PrintMsg("Deleted selected Items!");

	}
}

// Saving the action parameters

void ActionDelete::SaveComponentParameters(Component* Comp) {
	this->targetComponentsUndo.push(Comp);
	this->deletedComponentUndoCounter++;
}

void ActionDelete::SaveConnectionParameters(Connection* Conn) {
	this->targetConnectionsUndo.push(Conn);
	this->deletedConnectionsUndoCounter++;
}

void ActionDelete::Undo()
{
	// Looping over the ActionDelete Undo & Redo Stacks and recover the deleted items
	for (int i = 0; i < this->deletedComponentUndoCounter; i++) {
		pManager->AddComponent(this->targetComponentsUndo.top());
		this->targetComponentsRedo.push(this->targetComponentsUndo.top());
		this->targetComponentsUndo.pop();
	}
	swap(this->deletedComponentRedoCounter, this->deletedComponentUndoCounter);

	for (int i = 0; i < this->deletedConnectionsUndoCounter; i++) {
		pManager->AddConnection(this->targetConnectionsUndo.top());
		this->targetConnectionsRedo.push(this->targetConnectionsUndo.top());
		this->RestoreConnection(this->targetConnectionsUndo.top());
		this->targetConnectionsUndo.pop();
	}
	swap(this->deletedConnectionsRedoCounter, this->deletedConnectionsUndoCounter);
}

void ActionDelete::Redo()
{
	// Looping over the ActionDelete Undo & Redo Stacks and redelete the recovered items
	for (int i = 0; i < this->deletedComponentRedoCounter; i++) {
		pManager->MakeCompNull(this->targetComponentsRedo.top());
		this->targetComponentsUndo.push(this->targetComponentsRedo.top());
		this->targetComponentsRedo.pop();
	}
	swap(this->deletedComponentRedoCounter, this->deletedComponentUndoCounter);

	for (int i = 0; i < this->deletedConnectionsRedoCounter; i++) {
		pManager->AddConnection(this->targetConnectionsRedo.top());
		pManager->MakeConnNull(this->targetConnectionsRedo.top());
		this->targetConnectionsUndo.push(this->targetConnectionsRedo.top());
		this->targetConnectionsRedo.pop();
	}
	swap(this->deletedConnectionsRedoCounter, this->deletedConnectionsUndoCounter);
}

// Restoring the connection between the associated components
void ActionDelete::RestoreConnection(Connection* conn) {
	Component* Comp1 = conn->getComp1();
	Component* Comp2 = conn->getComp2();

	ConnectionInfo* connInfo = conn->getConnInfo();

	// Connect to the correct terminals

	switch (connInfo->item1_terminal) {
	case 0:
		Comp1->setTerm1Conn(conn);
		break;
	case 1:
		Comp1->setTerm2Conn(conn);
		break;
	}

	switch (connInfo->item2_terminal) {
	case 0:
		Comp2->setTerm1Conn(conn);
		break;
	case 1:
		Comp2->setTerm2Conn(conn);
		break;
	}
}

ActionDelete::~ActionDelete() {
	// Deleting Dynamic Objects of type Component
	while (!this->targetComponentsRedo.empty()) delete targetComponentsRedo.top(), targetComponentsRedo.pop(); // Clearing the Redo Stack Objects from memory
	while (!this->targetComponentsUndo.empty()) delete targetComponentsUndo.top(), targetComponentsUndo.pop(); // Clearing the Undo Stack Objects from memory

	while (!this->targetConnectionsRedo.empty()) delete targetConnectionsRedo.top(), targetConnectionsRedo.pop(); // Clearing the Redo Stack Objects from memory
	while (!this->targetConnectionsUndo.empty()) delete targetConnectionsUndo.top(), targetConnectionsUndo.pop(); // Clearing the Undo Stack Objects from memory

}