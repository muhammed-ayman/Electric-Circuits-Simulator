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
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	ofstream saveFile;
	saveFile.open("Saves\\circuit.txt");

	saveFile << CompCount << "\n";

	for (int i = 0; i < CompCount; i++) {
		string* comData = CompList[i]->Save();
		comData[1] = to_string(i + 1);

		saveFile << comData[0] << ", ";
		saveFile << comData[1] << ", ";
		saveFile << comData[2] << ", ";
		saveFile << comData[3] << ", ";
		saveFile << comData[4] << ", ";
		saveFile << comData[5] << "\n";
	}

	saveFile << "Connections" << "\n";
	saveFile << ConnCount << "\n";

	for (int i = 0; i < ConnCount; i++) {
		string* conData = ConnList[i]->Save();

		saveFile << conData[0] << ", ";
		saveFile << conData[1] << ", ";
		saveFile << conData[2] << ", ";
		saveFile << conData[3] << "\n";
	}

	saveFile.close();


	//Print Action Message
	pUI->PrintMsg("Circuit Saved");
}

void ActionSave::Undo()
{}

void ActionSave::Redo()
{}