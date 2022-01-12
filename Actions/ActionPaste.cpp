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

	if (!pUI->getWriteMode()) {
		pUI->PrintMsg("You can not perform this action");
		return;
	}

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


	if (Cx < 1100 && Cx > 20 && Cy >= 130 && Cy < 550) {

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
		this->SaveActionParameters(Clone, Clone->getTerm1Conn(), Clone->getTerm2Conn());
		pManager->ResetClonedComponent();
	}
	else pUI->PrintMsg("Cannot draw except in the drawing area!");
}

void ActionPaste::SaveActionParameters(Component* Comp, Connection* Conn1, Connection* Conn2) {
	this->Comp = Comp;
	this->Conn1 = Conn1;
	this->Conn2 = Conn2;
}

void ActionPaste::Undo()
{
	pManager->MakeCompNull(this->Comp);
	if (this->Comp->getTerm1Conn()) pManager->MakeConnNull(this->Comp->getTerm1Conn());
	if (this->Comp->getTerm2Conn()) pManager->MakeConnNull(this->Comp->getTerm2Conn());
}

void ActionPaste::Redo()
{
	pManager->AddComponent(this->Comp);
	if (this->Conn1) pManager->RestoreConnection(Conn1);
	if (this->Conn2) pManager->RestoreConnection(Conn2);
	pManager->ResetClonedComponent();
}


