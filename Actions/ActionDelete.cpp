#include "ActionDelete.h"
#include "..\ApplicationManager.h"

ActionDelete::ActionDelete(ApplicationManager* pApp) : Action(pApp)
{
}

ActionDelete::~ActionDelete(void)
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
				this->deletedComponentCounters++;
			}
		}
		pUI->PrintMsg("Deleted selected components!");
	}
}

void ActionDelete::SaveComponentParameters(Component* Comp) {
	this->targetComponents.push(Comp);
}

void ActionDelete::Undo()
{
	for (int i = 0; i < this->deletedComponentCounters; i++) {
		pManager->AddComponent(this->targetComponents.top());
		this->targetComponents.pop();
	}
}

void ActionDelete::Redo()
{
	this->Execute();
}