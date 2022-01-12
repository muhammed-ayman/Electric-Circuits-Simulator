#include "ActionMove.h"
#include "../Components/Component.h"
#include "../ApplicationManager.h"
#include <iostream>
#include <windows.h>

ActionMove::ActionMove(ApplicationManager* pApp) :Action(pApp)
{
}

ActionMove::~ActionMove(void)
{
}

void ActionMove::Execute()
{

	// Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	pManager->CloneSelectedComponent(); // Clone the current selected component to the temporary component variable

	Component* CompList[MaxCompCount];
	pManager->GetComponentList(CompList);
	Component* Comp = CompList[pManager->getSelectedComponentId()];

	// Get reference to the pWind
	window* pWind = pUI->getpWind();
	
	int iX = 0; int iY = 0;

	// Get Terminal Connections of the Component
	Connection* conn1 = Comp->getTerm1Conn();
	Connection* conn2 = Comp->getTerm2Conn();

	int comp1Terminal = 0; int comp2Terminal = 0;
	Component* comp1 = nullptr; Component* comp2 = nullptr;

	// Get the correct connection terminal
	if (conn1 != nullptr) {
		comp1 = conn1->getComp1();
		if (conn1->getComp1() == Comp) comp1 = conn1->getComp2();
		comp1Terminal = 0;
		if (comp1->getTerm2Conn() == conn1) comp1Terminal = 1;
	}

	if (conn2 != nullptr) {
		comp2 = conn2->getComp1();
		if (conn2->getComp1() == Comp) comp2 = conn2->getComp2();
		comp2Terminal = 0;
		if (comp2->getTerm2Conn() == conn2) comp2Terminal = 1;
	}

	// Loop until the button is down
	char cKeyData;
	bool bDragging = false;
	while (pWind->GetButtonState(LEFT_BUTTON, iX, iY) != BUTTON_DOWN) {
		pWind->GetMouseCoord(iX, iY);
		GraphicsInfo* gInfo = Comp->getGraphicsInfo();

		double compCenterX = (gInfo->PointsList[0].x + gInfo->PointsList[1].x) / 2;
		double compCenterY = (gInfo->PointsList[0].y + gInfo->PointsList[1].y) / 2;

		gInfo->PointsList[0].x = iX - pUI->getCompWidth()/2;
		gInfo->PointsList[0].y = iY - pUI->getCompHeight()/2;
		gInfo->PointsList[1].x = pUI->getCompWidth()/2 + iX;
		gInfo->PointsList[1].y = pUI->getCompHeight()/2 + iY;

		// Reconstruct the connections if not null upon screen refresh
		if (conn1 != nullptr) {
			GraphicsInfo* connInfo1 = conn1->getGraphicsInfo();
			connInfo1->PointsList[0].x = gInfo->PointsList[0].x;
			connInfo1->PointsList[0].y = gInfo->PointsList[0].y + pUI->getCompHeight() / 2;
			if (comp1Terminal == 0) {
				connInfo1->PointsList[1].x = comp1->getGraphicsInfo()->PointsList[0].x;
				connInfo1->PointsList[1].y = comp1->getGraphicsInfo()->PointsList[0].y + pUI->getCompHeight() / 2;
			}
			else {
				connInfo1->PointsList[1].x = comp1->getGraphicsInfo()->PointsList[1].x;
				connInfo1->PointsList[1].y = comp1->getGraphicsInfo()->PointsList[1].y - pUI->getCompHeight() / 2;
			}
		}

		if (conn2 != nullptr) {
			GraphicsInfo* connInfo2 = conn2->getGraphicsInfo();
			connInfo2->PointsList[0].x = gInfo->PointsList[1].x;
			connInfo2->PointsList[0].y = gInfo->PointsList[1].y - pUI->getCompHeight() / 2;
			if (comp2Terminal == 0) {
				connInfo2->PointsList[1].x = comp2->getGraphicsInfo()->PointsList[0].x;
				connInfo2->PointsList[1].y = comp2->getGraphicsInfo()->PointsList[0].y + pUI->getCompHeight() / 2;
			}
			else {
				connInfo2->PointsList[1].x = comp1->getGraphicsInfo()->PointsList[1].x;
				connInfo2->PointsList[1].y = comp1->getGraphicsInfo()->PointsList[1].y - pUI->getCompHeight() / 2;
			}
		}

		// Clear & Re-draw the Screen Area
		pUI->ClearDrawingArea();
		pUI->ClearStatusBar();
		pUI->CreateDrawingArea();
		pManager->UpdateInterface();
		Sleep(20);
	}
}

void ActionMove::Undo()
{}

void ActionMove::Redo()
{}

