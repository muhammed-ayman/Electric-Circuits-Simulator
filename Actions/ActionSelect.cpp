#include "ActionSelect.h"
#include "../ApplicationManager.h"
#include "ActionAddMenu.h"
#include "../Defs.H"
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

	Component* CompList[200];

	pManager->GetComponentList(CompList);

	int clicked = 0; // Initializing the click status as false (no-click)
	// Looping over the list of components (max = 200)
	for (int i = 0; i < 200; i++) {
		// If there is a component inside the drawing area, proceed
		if (CompList[i] != nullptr) {
			// Gets the graphical info of component [i]
			GraphicsInfo *CompListGraphicsInfo = CompList[i]->getGraphicsInfo();
			// If the x & y of the mouse lies within the area of the component, make it highlighted and display its information
			if (x >= CompListGraphicsInfo->PointsList[0].x && x <= CompListGraphicsInfo->PointsList[1].x && y >= CompListGraphicsInfo->PointsList[0].y && y <= CompListGraphicsInfo->PointsList[1].y) {
				clicked = 1; // Change the clicked status to true every time a component is clicked
				CompList[i]->setClick(true); // setClick(true) makes drawResistor use the highlighted image
				pManager->setSelectedComponentId(i); // Setting the selected component ID as the one currently clicked from the component list
				Menu->DrawComponentMenu(CompList[i]); // Drawing component menu as per the last selected component
			}
		}
	}

	// If the user clicks outside any of the components
	if (clicked == 0) {
		pUI->ClearStatusBar();
		for (int i = 0; i < 200; i++) {
			// If there is component, proceed
			if (CompList[i] != nullptr) {
				CompList[i]->setClick(false); // Unselects all the components (unhighlighting the images)
			}
		}
		pUI->ClearEditMenu(); // Clearning the edit menu once the user clicks outside the components

		pManager->setSelectedComponentId(-1); // Re-setting the selected component ID to -1 indicating that there is currently no selected component
	}

	delete Menu; // Freeing the memory after unselecting all components
	Menu = nullptr;
}

void ActionSelect::Undo()
{}

void ActionSelect::Redo()
{}

