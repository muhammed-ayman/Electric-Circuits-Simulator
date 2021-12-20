#include "ApplicationManager.h"
#include "Actions\ActionAddRes.h"
#include "Actions\ActionAddBulb.h"
#include "Actions\ActionAddBattery.h"
#include "Actions\ActionAddSwitch.h"
#include "Actions\ActionAddGround.h"
#include "Actions\ActionAddBuzzer.h"
#include "Actions\ActionAddFuse.h"
#include "Actions\ActionSimWindow.h"
#include "Actions\ActionSelect.h"
#include "Actions\ActionEditLabel.h"
#include "Actions\ActionDsnWindow.h"
#include "Actions\ActionEditValue.h"
#include "Actions\ActionAddConn.h"
#include "Actions\ActionSave.h"
#include "Actions\ActionLoad.h"
#include "Actions\ActionExit.h"

ApplicationManager::ApplicationManager()
{
	ResetData();
	//Creates the UI Object & Initialize the UI
	pUI = new UI;
}


void ApplicationManager::ResetData() {
	CompCount = 0;
	ConnCount = 0;

	for (int i = 0; i < MaxCompCount; i++)
		CompList[i] = nullptr;

	for (int i = 0; i < MaxConnCount; i++)
		ConnList[i] = nullptr;
}

////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;		
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return pUI->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = nullptr;
	switch (ActType)
	{
		case ADD_RESISTOR:
			pAct= new ActionAddRes(this);
			break;

		case ADD_BULB:
			pAct = new ActionAddBulb(this);
			break;

		case ADD_BATTERY:
			pAct = new ActionAddBattery(this);
			break;

		case ADD_SWITCH:
			pAct = new ActionAddSwitch(this);
			break;

		case ADD_GROUND:
			pAct = new ActionAddGround(this);
			break;

		case ADD_BUZZER:
			pAct = new ActionAddBuzzer(this);
			break;

		case ADD_FUSE:
			pAct = new ActionAddFuse(this);
			break;
		case SELECT:
			pAct = new ActionSelect(this);
			break;

		case ADD_CONNECTION:
			pAct = new ActionAddConn(this);
			break;

		case EDIT_Label:
			if (this->SelectedComponentId >= 0 || this->SelectedConnectionId >= 0) {
				pAct = new ActionEditLabel(this);
			}
			break;

		case DSN_MODE:
			pAct = new ActionDsnWindow(this);
			break;

		case EDIT_Value:
			if (this->SelectedComponentId >= 0) {
				pAct = new ActionEditValue(this);
			}
			break;

		case SIM_MODE:
			pAct = new ActionSimWindow(this);
			break;

		case SAVE:
			pAct = new ActionSave(this);
			break;

		case LOAD:
			pAct = new ActionLoad(this);
			break;

		case EXIT:
			pAct = new ActionExit(this);
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = nullptr;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	for (int i = 0; i < CompCount; i++) {
		CompList[i]->Draw(pUI);
		if (CompList[i]->getTerm1Conn() != nullptr) {
			CompList[i]->getTerm1Conn()->Draw(pUI);
		}
		if (CompList[i]->getTerm2Conn() != nullptr) {
			CompList[i]->getTerm2Conn()->Draw(pUI);
		}

	}

}

////////////////////////////////////////////////////////////////////
UI* ApplicationManager::GetUI()
{
	return pUI;
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < CompCount; i++) {
		delete CompList[i];
		CompList[i] = nullptr;
	}
	delete pUI;
	pUI = nullptr;
}

///////////////////////////////////////////////////////////////////

void ApplicationManager::GetComponentList(Component* CompListNew[]) {
	for (int i = 0; i < MaxCompCount; i++) {
		CompListNew[i] = CompList[i];
	}
}

void ApplicationManager::GetConnectionList(Connection* ConnListNew[]) {
	for (int i = 0; i < MaxConnCount; i++) {
		ConnListNew[i] = ConnList[i];
	}
}

int ApplicationManager::GetComponentCount() {
	return CompCount;
}

int ApplicationManager::GetConnectionCount() {
	return ConnCount;
}

///////////////////////////////////////////////////////////////////

void ApplicationManager::setSelectedComponentId(int selectedCompId) {
	this->SelectedComponentId = selectedCompId;
}

int ApplicationManager::getSelectedComponentId() {
	return this->SelectedComponentId;
}


////////////////////////////////////////////////////////////////////

void ApplicationManager::setSelectedConnectionId(int selectedConnId) {
	this->SelectedConnectionId = selectedConnId;
}

int ApplicationManager::getSelectedConnectionId() {
	return this->SelectedConnectionId;
}



// List of Connections

void ApplicationManager::AddConnection(Connection* pConn)
{
	ConnList[ConnCount++] = pConn;
}


/////////////////////////////////////////////////////////

void ApplicationManager::LoadCircuit(string*** parsedData, int comCount, int conCount) {

	//reset application manager
	ResetData();


	GraphicsInfo* pGInfo;
	Component* pR;
	// load components part
	for (int comIndex = 0; comIndex < comCount; comIndex++) {
		pGInfo = new GraphicsInfo(2);

		int compWidth = pUI->getCompWidth();
		int compHeight = pUI->getCompHeight();

		pGInfo->PointsList[0].x = stoi(parsedData[0][comIndex][4]);
		pGInfo->PointsList[0].y = stoi(parsedData[0][comIndex][5]);
		pGInfo->PointsList[1].x = stoi(parsedData[0][comIndex][4]) + compWidth;
		pGInfo->PointsList[1].y = stoi(parsedData[0][comIndex][5]) + compHeight;

		string compType = parsedData[0][comIndex][0];

		if (compType == "RES") pR = new Resistor(pGInfo);
		else if (compType == "BLB")  pR = new Bulb(pGInfo);
		else if (compType == "BAT") pR = new Battery(pGInfo);
		else if (compType == "SWT") pR = new Switch(pGInfo);
		else if (compType == "GND") pR = new Ground(pGInfo);
		else if (compType == "BUZ") pR = new Buzzer(pGInfo);
		else if (compType == "FUS") pR = new Fuse(pGInfo);
		else pR = nullptr;

		if (pR) {
			pR->setLabel(parsedData[0][comIndex][2]);
			pR->setValue(stod(parsedData[0][comIndex][3]));
			AddComponent(pR);
		}
		
	}

	for (int conIndex = 0; conIndex < conCount; conIndex++) {
		ConnectionInfo* cInfo = new ConnectionInfo;
		ActionAddConn* AddConnection = new ActionAddConn(this);

		cInfo->component1 = stoi(parsedData[1][conIndex][0])-1;
		cInfo->component2 = stoi(parsedData[1][conIndex][1])-1;
		cInfo->item1_terminal = stoi(parsedData[1][conIndex][2]);
		cInfo->item2_terminal = stoi(parsedData[1][conIndex][3]);
		AddConnection->ProcessConnection(cInfo);
	}
	

	UpdateInterface();
}