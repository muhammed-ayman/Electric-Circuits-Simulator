#include "ActionCut.h"
#include "../ApplicationManager.h"

ActionCut::ActionCut(ApplicationManager* pApp) :Action(pApp)
{
}

ActionCut::~ActionCut(void)
{
}

void ActionCut::Execute()
{

	// Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	pManager->CloneSelectedComponent(); // Clone the selected componenet
	
	// Get the Component List, save the component parameters, and make it null
	Component* CompList[MaxCompCount];
	pManager->GetComponentList(CompList);
	Component* SelectedComponent = CompList[pManager->getSelectedComponentId()];
	pManager->MakeCompNull(SelectedComponent); // Delete the selected component

	this->SaveActionParameters(SelectedComponent, SelectedComponent->getTerm1Conn(), SelectedComponent->getTerm2Conn());

	if (SelectedComponent->getTerm1Conn()) pManager->MakeConnNull(SelectedComponent->getTerm1Conn());
	if (SelectedComponent->getTerm2Conn()) pManager->MakeConnNull(SelectedComponent->getTerm2Conn());

	pUI->PrintMsg("Component Cut");
}

void ActionCut::SaveActionParameters(Component* Comp, Connection* Conn1, Connection* Conn2) {
	this->Comp = Comp;
	this->Conn1 = Conn1;
	this->Conn2 = Conn2;
}

void ActionCut::Undo()
{
	pManager->AddComponent(this->Comp);
	if (this->Conn1) pManager->RestoreConnection(Conn1);
	if (this->Conn2) pManager->RestoreConnection(Conn2);
	pManager->ResetClonedComponent();
}

void ActionCut::Redo()
{
	pManager->MakeCompNull(this->Comp);
	if (this->Comp->getTerm1Conn()) pManager->MakeConnNull(this->Comp->getTerm1Conn());
	if (this->Comp->getTerm2Conn()) pManager->MakeConnNull(this->Comp->getTerm2Conn());
}

