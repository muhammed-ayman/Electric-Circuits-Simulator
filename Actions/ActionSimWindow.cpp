#include "ActionSimWindow.h"
#include "..\ApplicationManager.h"

ActionSimWindow::ActionSimWindow(ApplicationManager* pApp) :Action(pApp)
{
}

ActionSimWindow::~ActionSimWindow(void)
{
}

bool ActionSimWindow::Validate() {
	int counter = 0;
	Component* CompList[200];
	pManager->GetComponentList(CompList);
	if (pManager->GetGroundCount() == 1 && (pManager->GetComponentCount() == pManager->GetConnectionCount())) {
		for (int i = 0; i < pManager->GetComponentCount(); i++) {
			if (CompList[i] != nullptr) {
				if (!(pManager->isGround(CompList[i])) && !(pManager->isSwitch(CompList[i]))) {
					if (pManager->getCompValue(CompList[i]) > double(0) && pManager->getCompLabel(CompList[i]) != "Component") counter++;
				}
				if (pManager->isSwitch(CompList[i])) {
					if ((pManager->getCompValue(CompList[i]) == double(0) || pManager->getCompValue(CompList[i]) == double(1)) && pManager->getCompLabel(CompList[i]) != "Component")counter++;
				}
				if(pManager->isGround(CompList[i])) {
					if (pManager->getCompValue(CompList[i]) == double(0) && pManager->getCompLabel(CompList[i]) != "Component") counter++;
				}
			}
		}
	}
	if (counter == pManager->GetComponentCount()) return true;
	return false;
}

void ActionSimWindow::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	if (Validate()) {
		// unselecting selected objects in simulation mode
		Component* CompList[200];
		pManager->GetComponentList(CompList);
		for (int i = 0; i < 200; i++) {
			if (CompList[i] != nullptr) {
				CompList[i]->setClick(false);
			}
		}
		//creating simulation toolbar
		pUI->CreateSimulationToolBar();
		pUI->CreateDrawingArea();
		//Print Action Message
		pUI->PrintMsg("Simulation Mode Initialized");
	}
	else pUI->PrintMsg("Circuit is not valid! One circuit, one ground (val=0), and full connections, labels, & values! Switch = 0 or 1!");
}

void ActionSimWindow::Undo()
{
}

void ActionSimWindow::Redo()
{
}
