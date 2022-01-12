#include "ActionDsnWindow.h"
#include "..\ApplicationManager.h"

ActionDsnWindow::ActionDsnWindow(ApplicationManager* pApp) :Action(pApp)
{
}

ActionDsnWindow::~ActionDsnWindow(void)
{
}

bool ActionDsnWindow::Validate() {
	//Component* CompList[MaxCompCount];
	//Connection* ConnList[MaxConnCount];

	//pManager->GetComponentList(CompList);
	//pManager->GetConnectionList(ConnList);

	int CompCount = pManager->GetComponentCount();
	int ConnCount = pManager->GetConnectionCount();

	if (CompCount - ConnCount == 1) {
		return true;
	}
	else {
		return false;
	}

	//for (int i = 0; i < CompCount; i++) {
	//	Connection* term1 = CompList[i]->getTerm1Conn();
	//	Connection* term2 = CompList[i]->getTerm2Conn();

	//	ConnectionInfo* cinfo_term1 = term1->getConnInfo();
	//	ConnectionInfo* cinfo_term2 = term2->getConnInfo();

	//	if (cinfo_term1->component1 == cinfo_term2->component2 && cinfo_term1->component2 == cinfo_term2->component1) return false;
	//}

}
			

void ActionDsnWindow::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	if (pManager->GetUI()->getAppMode() == MODULE) {
		if (!pManager->GetUI()->getWriteMode()) {
			Component* CompList[MaxCompCount];

			pManager->GetComponentList(CompList);
			
			int value = (1 / ((1 /(CompList[0]->getValue() + CompList[1]->getValue())) + (1 / (CompList[2]->getValue() + CompList[3]->getValue()))));

			//Component* TempCompList[MaxCompCount];
			//pManager->GetTempComponentList(TempCompList);
			//TempCompList[pManager->getTempSelectedComponentId]->setValue(value);
			pManager->GetUI()->setWriteMode(true);
		}
		else if (Validate()) {
			int value = 0;
			Component* CompList[MaxCompCount];

			pManager->GetComponentList(CompList);

			for (int i = 0; i < pManager->GetComponentCount(); i++) {
				value += CompList[i]->getValue();
			}

			Component* TempCompList[MaxCompCount];
			pManager->GetTempComponentList(TempCompList);
		}
		else {
			pUI->PrintMsg("Failed to validate the module");
			return;
		}
	}
	

	pManager->RevertTemp();
	pManager->UpdateInterface();
	pUI->ClearDrawingArea();
	pUI->CreateDrawingArea();
	//creating design mode toolbar
	pUI->CreateDesignToolBar();
	//Print Action Message
	pUI->PrintMsg("Back to design mode");
}

void ActionDsnWindow::Undo()
{
}

void ActionDsnWindow::Redo()
{
}
