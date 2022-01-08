#include "ActionPaste.h"
#include "../ApplicationManager.h"

ActionPaste::ActionPaste(ApplicationManager* pApp) :Action(pApp)
{
}

ActionPaste::~ActionPaste(void)
{
}

void ActionPaste::Execute()
{

	// Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	Component* Clone = pManager->getClonedComponent(); // Retrieve the cloned componenet if exists

	if (!Clone) {
		pUI->PrintMsg("There are no saved components");
		return;
	}

	pUI->PrintMsg("Select location to place the cutted component");

	//Get Center point of the area where the Comp should be drawn
	pUI->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pUI->ClearStatusBar();


	if (Cx < 980 && Cx > 20 && Cy >= 130 && Cy < 550) {

		GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the Comp

		//Calculate the rectangle Corners
		int compWidth = pUI->getCompWidth();
		int compHeight = pUI->getCompHeight();

		pGInfo->PointsList[0].x = Cx - compWidth / 2;
		pGInfo->PointsList[0].y = Cy - compHeight / 2;
		pGInfo->PointsList[1].x = Cx + compWidth / 2;
		pGInfo->PointsList[1].y = Cy + compHeight / 2;

		Clone->setGraphicsInfo(pGInfo);
		pManager->AddComponent(Clone);
		pManager->ResetClonedComponent();
	}
	else pUI->PrintMsg("Cannot draw except in the drawing area!");
}

void ActionPaste::Undo()
{}

void ActionPaste::Redo()
{}

