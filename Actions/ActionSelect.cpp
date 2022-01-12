#include "ActionSelect.h"
#include "../ApplicationManager.h"
#include "ActionAddMenu.h"
#include <sstream>

ActionSelect::ActionSelect(ApplicationManager* pApp) :Action(pApp)
{
}


ActionSelect::~ActionSelect(void)
{

}

void ActionSelect::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	int x=0, y=0;

	// Retrieves the mouse coordinates clicked by the user
	pUI->GetLastPointClicked(x, y);

	// Initializing the pointer to the ActionAddMenu
	ActionAddMenu* Menu = new ActionAddMenu(pManager);

	Component* CompList[MaxCompCount];

	pManager->GetComponentList(CompList);

	int clicked = 0; // Initializing the click status as false (no-click)
	// Looping over the list of components (max = 200)
	for (int i = 0; i < MaxCompCount; i++) {
		// If there is a component inside the drawing area, proceed
		if (CompList[i] != nullptr) {
			// Gets the graphical info of component [i]
			GraphicsInfo* CompListGraphicsInfo = CompList[i]->getGraphicsInfo();
			// If the x & y of the mouse lies within the area of the component, make it highlighted and display its information
			if (x >= CompListGraphicsInfo->PointsList[0].x && x <= CompListGraphicsInfo->PointsList[1].x && y >= CompListGraphicsInfo->PointsList[0].y && y <= CompListGraphicsInfo->PointsList[1].y) {
				pUI->PrintMsg("Component Clicked");
				clicked = 1; // Change the clicked status to true every time a component is clicked
				CompList[i]->setClick(true); // setClick(true) makes drawResistor use the highlighted image
				pManager->setSelectedComponentId(i); // Setting the selected component ID as the one currently clicked from the component list
				
				if (pUI->getAppMode() != SIMULATION) {
					Menu->DrawComponentMenu(CompList[i]); // Drawing component menu as per the last selected component
				}
				else {
					if ((CompList[i]->GetItemType()) == "SWT") {
						CompList[i]->setClosed(!CompList[i]->isClosed());
						pManager->updateCircuitState();
					}
				}
			}
		}
		else break;
	}


	Connection* ConnList[MaxConnCount];

	pManager->GetConnectionList(ConnList);

	if (clicked == 0) {
		for (int i = 0; i < MaxConnCount; i++) {
			if (ConnList[i] != nullptr) {
				cout << "Connection is not null: " << i << endl;
				GraphicsInfo* ConnListGraphicsInfo = ConnList[i]->getGraphicsInfo();
				double lineSlope = double(ConnListGraphicsInfo->PointsList[0].y
					- ConnListGraphicsInfo->PointsList[1].y) / (ConnListGraphicsInfo->PointsList[0].x
						- ConnListGraphicsInfo->PointsList[1].x);

				double lineIntercept = ConnListGraphicsInfo->PointsList[0].y - lineSlope * ConnListGraphicsInfo->PointsList[0].x;

				double expectedY = lineSlope * x + lineIntercept;
				double leftX = ConnListGraphicsInfo->PointsList[1].x;
				double rightX = ConnListGraphicsInfo->PointsList[0].x;
				double deltaY = 10;

				if (leftX > rightX) {
					swap(leftX, rightX);
				}

				// Press Info:
				//cout << "Line equation: " << "y=" << lineSlope << "*x" << "+" << lineIntercept << endl;
				//cout << "You pressed on (" << x << "," << y << ")" << endl;
				//cout << "Expected Y is " << expectedY << endl;

				if (rightX - leftX < 10) {
					expectedY = double(ConnListGraphicsInfo->PointsList[0].y + ConnListGraphicsInfo->PointsList[1].y) / 2;
					deltaY = double(abs(ConnListGraphicsInfo->PointsList[0].y - ConnListGraphicsInfo->PointsList[1].y)) / 2;
				}


				if (y <= expectedY + deltaY && y >= expectedY - deltaY && x >= leftX - 5 && x <= rightX + 5) {
					pUI->PrintMsg("Connection Clicked");
					clicked = 1;
					ConnList[i]->setClick(true);
					pManager->setSelectedConnectionId(i);
					Menu->DrawConnectionMenu(ConnList[i]);	
					
					break;
				}
			}
			else break;
		}
	}

	// If the user clicks outside any of the components
	if (clicked == 0) {
		pUI->ClearStatusBar();
		for (int i = 0; i < MaxCompCount; i++) {
			// If there is component, proceed
			if (CompList[i] != nullptr) {
				CompList[i]->setClick(false); // Unselects all the components (unhighlighting the images)
				pManager->setSelectedComponentId(-1);
			}
		}
		for (int i = 0; i < MaxConnCount; i++) {
			// If there is connection, proceed
			if (ConnList[i] != nullptr) {
				ConnList[i]->setClick(false); // Unselects all the connections (unhighlighting the lines)
			}
		}
		pUI->ClearEditMenu(); // Clearning the edit menu once the user clicks outside the components
		pUI->CreateDrawingArea();
		pManager->setSelectedComponentId(-1); // Re-setting the selected component ID to -1 indicating that there is currently no selected component
		pManager->setSelectedConnectionId(-1); // Re-setting the selected connection ID to -1 indicating that there is currently no selected connection
	}

	delete Menu; // Freeing the memory after unselecting all components
	Menu = nullptr;
}

void ActionSelect::Undo()
{}

void ActionSelect::Redo()
{}

