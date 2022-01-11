#include "ActionSave.h"
#include "..\ApplicationManager.h"

ActionSave::ActionSave(ApplicationManager* pApp) :Action(pApp)
{
	pManager->GetComponentList(CompList);
	pManager->GetConnectionList(ConnList);
	CompCount = pManager->GetComponentCount();
	ConnCount = pManager->GetConnectionCount();
}

ActionSave::~ActionSave(void)
{
}

void ActionSave::Execute()
{


	//appMode
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	ofstream saveFile;
	saveFile.open("Saves\\circuit.txt");

	saveFile << CompCount << "\n";

	for (int i = 0; i < CompCount; i++) {
		CompList[i]->Save(saveFile, to_string(i + 1));
	}

	saveFile << "Connections" << "\n";
	saveFile << ConnCount << "\n";

	for (int i = 0; i < ConnCount; i++) {
		ConnList[i]->Save(saveFile, to_string(i + 1));
	}

	saveFile.close();


	//Print Action Message
	pUI->PrintMsg("Circuit Saved");
}

void ActionSave::Undo()
{}

void ActionSave::Redo()
{}