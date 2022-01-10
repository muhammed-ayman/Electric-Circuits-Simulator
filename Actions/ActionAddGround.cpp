#include "ActionAddGround.h"
#include "..\ApplicationManager.h"

ActionAddGround::ActionAddGround(ApplicationManager* pApp) :Action(pApp)
{
}

ActionAddGround::~ActionAddGround(void)
{
}

void ActionAddGround::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("Adding a new ground: Click anywhere to add");

	//Get Center point of the area where the Comp should be drawn
	pUI->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pUI->ClearStatusBar();


	if (Cx < 1100 && Cx > 20 && Cy >= 130 && Cy < 550) {

		GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the Comp

		//Calculate the rectangle Corners
		int compWidth = pUI->getCompWidth();
		int compHeight = pUI->getCompHeight();

		pGInfo->PointsList[0].x = Cx - compWidth / 2;
		pGInfo->PointsList[0].y = Cy - compHeight / 2;
		pGInfo->PointsList[1].x = Cx + compWidth / 2;
		pGInfo->PointsList[1].y = Cy + compHeight / 2;

		Ground* pR = new Ground(pGInfo);
		pManager->AddComponent(pR);
		this->SaveComponentParameters(pR);
	}
	else pUI->PrintMsg("Cannot draw except in the drawing area!");
}


void ActionAddGround::SaveComponentParameters(Ground* groundPointer) {
	this->GroundPointer = groundPointer;
}

void ActionAddGround::Undo()
{
	pManager->MakeCompNull(this->GroundPointer);
}

void ActionAddGround::Redo()
{
	pManager->AddComponent(this->GroundPointer);
}

