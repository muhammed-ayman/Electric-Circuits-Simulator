#include "ActionModWindow.h"
#include "..\ApplicationManager.h"

ActionModWindow::ActionModWindow(ApplicationManager* pApp) :Action(pApp)
{
}

ActionModWindow::~ActionModWindow(void)
{
}

bool ActionModWindow::Validate() {
	int counter = 0;
	Component* CompList[MaxCompCount];
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
				if (pManager->isGround(CompList[i])) {
					if (pManager->getCompValue(CompList[i]) == double(0) && pManager->getCompLabel(CompList[i]) != "Component") counter++;
				}
			}
		}
	}
	if (counter == pManager->GetComponentCount()) return true;
	return false;
}

void ActionModWindow::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	if (Validate()) {
		// unselecting selected objects in simulation mode
		Component* CompList[MaxCompCount];
		pManager->GetComponentList(CompList);
		for (int i = 0; i < MaxCompCount; i++) {
			if (CompList[i] != nullptr) {
				CompList[i]->setClick(false);
			}
		}

		Connection* Connlist[MaxConnCount];
		pManager->GetConnectionList(Connlist);
		for (int i = 0; i < MaxConnCount; i++) {
			if (Connlist[i] != nullptr) {
				Connlist[i]->setClick(false);
			}
		}

		//creating simulation toolbar
		pUI->CreateModuleToolBar();
		pUI->CreateDrawingArea();
		//Print Action Message
		pUI->PrintMsg("Module Mode Initialized");
	}
	else pUI->PrintMsg("Circuit is not valid! One circuit, one ground (val=0), and full connections, labels, & values! Switch = 0 or 1!");
}

void ActionModWindow::Undo()
{
}

void ActionModWindow::Redo()
{
}
