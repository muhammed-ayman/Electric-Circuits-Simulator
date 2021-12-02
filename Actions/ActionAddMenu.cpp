#include "ActionAddMenu.h"
#include "../ApplicationManager.h"
#include <sstream>

ActionAddMenu::ActionAddMenu(ApplicationManager* pApp) :Action(pApp)
{
}


ActionAddMenu::~ActionAddMenu(void)
{
}

void ActionAddMenu::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	int x=0, y=0;

	pUI->GetLastPointClicked(x, y);

	Component* CompList[200];

	pManager->GetComponentList(CompList);

	int clicked = 0;
	for (int i = 0; i < 200; i++) {
		if (CompList[i] != nullptr) {
			GraphicsInfo *CompListGraphicsInfo = CompList[i]->getGraphicsInfo();
			if (x >= CompListGraphicsInfo->PointsList[0].x && x <= CompListGraphicsInfo->PointsList[1].x && y >= CompListGraphicsInfo->PointsList[0].y && y <= CompListGraphicsInfo->PointsList[1].y) {
				pUI->PrintMsg("Component Clicked");
				clicked = 1;
				CompList[i]->setClick(true);
			}
		}
	}

	if (clicked == 0) {
		pUI->ClearStatusBar();
		for (int i = 0; i < 200; i++) {
			if (CompList[i] != nullptr) {
				CompList[i]->setClick(false);
			}
		}
	}



}

void ActionAddMenu::Undo()
{}

void ActionAddMenu::Redo()
{}

