#include "ActionAddSwitch.h"
#include "..\ApplicationManager.h"

ActionAddSwitch::ActionAddSwitch(ApplicationManager* pApp) :Action(pApp)
{
}

ActionAddSwitch::~ActionAddSwitch(void)
{
}

void ActionAddSwitch::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("Adding a new switch: Click anywhere to add");

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

		Switch* pR = new Switch(pGInfo);
		pManager->AddComponent(pR);
		this->SaveComponentParameters(pR);
	}
	else pUI->PrintMsg("Cannot draw except in the drawing area!");
}

void ActionAddSwitch::SaveComponentParameters(Switch* switchPointer) {
	this->SwitchPointer = switchPointer;
}

void ActionAddSwitch::Undo()
{
	pManager->MakeCompNull(this->SwitchPointer);
}

void ActionAddSwitch::Redo()
{
	pManager->AddComponent(this->SwitchPointer);
}