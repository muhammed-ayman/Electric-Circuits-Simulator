#include "ActionAddBuzzer.h"
#include "..\ApplicationManager.h"

ActionAddBuzzer::ActionAddBuzzer(ApplicationManager* pApp) :Action(pApp)
{
}

ActionAddBuzzer::~ActionAddBuzzer(void)
{
}

void ActionAddBuzzer::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("Adding a new buzzer: Click anywhere to add");

	//Get Center point of the area where the Comp should be drawn
	pUI->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pUI->ClearStatusBar();


	if (Cx < 900 && Cx > 20 && Cy >= 130 && Cy < 550) {

		GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the Comp

		//Calculate the rectangle Corners
		int compWidth = pUI->getCompWidth();
		int compHeight = pUI->getCompHeight();

		pGInfo->PointsList[0].x = Cx - compWidth / 2;
		pGInfo->PointsList[0].y = Cy - compHeight / 2;
		pGInfo->PointsList[1].x = Cx + compWidth / 2;
		pGInfo->PointsList[1].y = Cy + compHeight / 2;

		Buzzer* pR = new Buzzer(pGInfo);
		pManager->AddComponent(pR);
	}
	else pUI->PrintMsg("Cannot draw except in the drawing area!");
}

void ActionAddBuzzer::Undo()
{}

void ActionAddBuzzer::Redo()
{}

