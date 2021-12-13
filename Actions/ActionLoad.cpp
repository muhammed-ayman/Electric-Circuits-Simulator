#include "ActionLoad.h"
#include "..\ApplicationManager.h"

ActionLoad::ActionLoad(ApplicationManager* pApp) :Action(pApp)
{
}

ActionLoad::~ActionLoad(void)
{
	// destruct parsedData here
}

void ActionLoad::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	
	string fileLines[MaxCompCount + MaxConnCount + 3];

	ifstream loadFile;
	loadFile.open("Saves\\circuit.txt");

	if (!loadFile)
	{
		pUI->PrintMsg("Circuit file not found");
		return;
	}

	int comCount = -1;
	int conCount = -1;
	int filesize = 0;
	string previous = "";

	for (string line; getline(loadFile, line);) {
		if (comCount == -1) {
			comCount = stoi(line);
			if (comCount > MaxCompCount) {
				pUI->PrintMsg("Max components count reached");
				return;
			}
		} 
		if (conCount == -1 && comCount != -1 && previous == "Connections") {
			conCount = stoi(line);
			if (conCount > MaxConnCount) {
				pUI->PrintMsg("Max connections count reached");
				return;
			}
		} 
		previous = line;
		fileLines[filesize] = line;
		filesize += 1;
	}

	if (comCount == -1 || conCount == -1) {
		pUI->PrintMsg("Corrupted file");
		return;
	}

	// array of parsed data
	string*** parsedData = new string **[4];
	parsedData[0] = new string * [comCount];
	parsedData[1] = new string * [conCount];

	for (int i = 0; i < comCount; i++) {
		parsedData[0][i] = new string[6];
	}

	for (int i = 0; i < conCount; i++) {
		parsedData[1][i] = new string[4];
	}
	
	int comCounter = 0;
	int conCounter = 0;

	for (int i = 0; i < filesize; i++) {
		if (i > 0 && i <= comCount) {
			char* pch;
			char* context = nullptr;
			char line[300];
			int index = 0;
			strcpy_s(line, fileLines[i].c_str());
			pch = strtok_s(line, ", ", &context);
			while (pch != NULL)
			{
				parsedData[0][comCounter][index] = pch;
				index += 1;
				pch = strtok_s(NULL, ", ", &context);
			}
			comCounter += 1;
		}
		else if (i > comCount +2) {
			char* pch;
			char* context = nullptr;
			char line[300];
			int index = 0;
			strcpy_s(line, fileLines[i].c_str());
			pch = strtok_s(line, ", ", &context);
			while (pch != NULL)
			{
				parsedData[1][conCounter][index] = pch;
				index += 1;
				pch = strtok_s(NULL, ", ", &context);
			}
			conCounter += 1;
		}
	}

	//load circut
	pManager->LoadCircuit(parsedData, comCount, conCount);

	//Print Action Message
	pUI->PrintMsg("Circuit Loaded");
}

void ActionLoad::Undo()
{}

void ActionLoad::Redo()
{}