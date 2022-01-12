#include "ActionLoad.h"
#include "..\ApplicationManager.h"

#include "../Components/Battery.h"
#include "../Components/Bulb.h"
#include "../Components/Buzzer.h"
#include "../Components/Fuse.h"
#include "../Components/Ground.h"
#include "../Components/Module.h"
#include "../Components/Resistor.h"
#include "../Components/Switch.h"

#include "../Components/Component.h"
#include "../Components/Connection.h"

#include "ActionAddConn.h"


ActionLoad::ActionLoad(ApplicationManager* pApp) :Action(pApp)
{
}

ActionLoad::~ActionLoad(void)
{

}

void ActionLoad::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	
	if (!pUI->getWriteMode() && pManager->GetComponentCount() > 0) {
		pUI->PrintMsg("You can not perform this action");
		return;
	}

	string fileLines[MaxCompCount + MaxConnCount + 3];

	pManager->ResetData();

	ifstream loadFile;

	pUI->PrintMsg("Type the file name");

	if (pUI->getAppMode() == MODULE) {
		if (pUI->getWriteMode()) {
			string filename = pUI->GetSrting();
			loadFile.open("Modules\\" + filename + ".txt");
		}
		else {
			loadFile.open("Modules\\default.txt");
		}
		
	}
	else {
		string filename = pUI->GetSrting();
		loadFile.open("Saves\\" + filename + ".txt");
	}

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
	string* LoadedComponent = new string[6];
	string* LoadedConnection = new string[4];
	
	int comCounter = 0;
	int conCounter = 0;

	GraphicsInfo* pGInfo;
	Component* pR;

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
				LoadedComponent[index] = pch;
				index += 1;
				pch = strtok_s(NULL, ", ", &context);
			}
			comCounter += 1;
			
			string compType = LoadedComponent[0];

			if (compType == "RES") pR = new Resistor();
			else if (compType == "BLB")  pR = new Bulb();
			else if (compType == "BAT") pR = new Battery();
			else if (compType == "SWT") pR = new Switch();
			else if (compType == "GND") pR = new Ground();
			else if (compType == "BUZ") pR = new Buzzer();
			else if (compType == "FUS") pR = new Fuse();
			else if (compType == "MOD") pR = new Module();
			else pR = nullptr;

			if (pR) {
				pGInfo = new GraphicsInfo(2);

				int compWidth = pUI->getCompWidth();
				int compHeight = pUI->getCompHeight();

				pGInfo->PointsList[0].x = stoi(LoadedComponent[4]);
				pGInfo->PointsList[0].y = stoi(LoadedComponent[5]);
				pGInfo->PointsList[1].x = stoi(LoadedComponent[4]) + compWidth;
				pGInfo->PointsList[1].y = stoi(LoadedComponent[5]) + compHeight;

				string label = LoadedComponent[2];
				double value = stod(LoadedComponent[3]);
				pR->Load(pGInfo, label, value);


				pManager->AddComponent(pR);
			}
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
				LoadedConnection[index] = pch;
				index += 1;
				pch = strtok_s(NULL, ", ", &context);
			}

			ConnectionInfo* cInfo = new ConnectionInfo;
			ActionAddConn* AddConnection = new ActionAddConn(pManager);

			cInfo->component1 = stoi(LoadedConnection[0]) - 1;
			cInfo->component2 = stoi(LoadedConnection[1]) - 1;
			cInfo->item1_terminal = stoi(LoadedConnection[2]);
			cInfo->item2_terminal = stoi(LoadedConnection[3]);
			AddConnection->ProcessConnection(cInfo);

			conCounter += 1;
		}
	}


	pManager->UpdateInterface();

	//load circut
	//pManager->LoadCircuit(parsedData, comCount, conCount);

	//Print Action Message
	pUI->PrintMsg("Circuit Loaded");

	delete[] LoadedComponent;
	delete[] LoadedConnection;
}

void ActionLoad::Undo()
{}

void ActionLoad::Redo()
{}