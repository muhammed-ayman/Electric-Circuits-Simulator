#include "ApplicationManager.h"
#include "Actions\ActionAddRes.h"
#include "Actions\ActionAddBulb.h"
#include "Actions\ActionAddBattery.h"
#include "Actions\ActionAddSwitch.h"
#include "Actions\ActionAddGround.h"
#include "Actions\ActionAddBuzzer.h"
#include "Actions\ActionAddFuse.h"
#include "Actions\ActionAddModule.h"
#include "Actions\ActionSimWindow.h"
#include "Actions\ActionSelect.h"
#include "Actions\ActionEditLabel.h"
#include "Actions\ActionDsnWindow.h"
#include "Actions\ActionModWindow.h"
#include "Actions\ActionEditValue.h"
#include "Actions\ActionAddConn.h"
#include "Actions\ActionSave.h"
#include "Actions\ActionLoad.h"
#include "Actions\ActionExit.h"
#include "Actions\ActionCopy.h"
#include "Actions\ActionCut.h"
#include "Actions\ActionPaste.h"
#include "Actions\ActionDelete.h"
#include "Actions\ActionRedo.h"
#include "Actions\ActionUndo.h"
#include "Actions\ActionCircuitLog.h"
#include "Actions\ActionMeasureVoltage.h"
#include "Actions\ActionMeausreCurrent.h"
#include <iostream>
#include <windows.h>
#include "MMSystem.h"
using namespace std;



ApplicationManager::ApplicationManager()
{
	ResetData();
	//Creates the UI Object & Initialize the UI
	pUI = new UI;
}

int ApplicationManager::GetGroundCount() {
	return GroundCount;
}

void ApplicationManager::ResetData() {
	CompCount = 0;
	ConnCount = 0;

	for (int i = 0; i < MaxCompCount; i++) {
		if(CompList[i]) delete CompList[i], delete Temp_CompList[i];
		CompList[i] = nullptr;
		Temp_CompList[i] = nullptr;
	}

	for (int i = 0; i < MaxConnCount; i++) {;
		if (ConnList[i]) delete ConnList[i], delete Temp_ConnList[i];
		ConnList[i] = nullptr;
		Temp_ConnList[i] = nullptr;
	}
		
}

void ApplicationManager::EmptyData() {
	CompCount = 0;
	ConnCount = 0;

	for (int i = 0; i < MaxCompCount; i++)
		CompList[i] = nullptr;

	for (int i = 0; i < MaxConnCount; i++)
		ConnList[i] = nullptr;
}

void ApplicationManager::EmptyTempData() {
	Temp_CompCount = 0;
	Temp_ConnCount = 0;
	TempSelectedComponentId = -1;

	for (int i = 0; i < MaxCompCount; i++)
		Temp_CompList[i] = nullptr;

	for (int i = 0; i < MaxConnCount; i++)
		Temp_ConnList[i] = nullptr;
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
			GroundCount++;
			break;

		case ADD_BUZZER:
			pAct = new ActionAddBuzzer(this);
			break;

		case ADD_FUSE:
			pAct = new ActionAddFuse(this);
			break;
		
		case ADD_MODULE:
			pAct = new ActionAddModule(this);
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

		case EDIT_Value:
			if (this->SelectedComponentId >= 0 && !dynamic_cast<Module*>(CompList[this->SelectedComponentId])){
				pAct = new ActionEditValue(this);
			}
			else if (this->SelectedComponentId >= 0 && dynamic_cast<Module*>(CompList[this->SelectedComponentId])) {
				pAct = new ActionModWindow(this);
			}
			break;

		case EDIT_Copy:
			if (this->SelectedComponentId >= 0) {
				pAct = new ActionCopy(this);
			}
			break;

		case EDIT_Cut:
			if (this->SelectedComponentId >= 0) {
				pAct = new ActionCut(this);
			}
			break;

		case PASTE:
			pAct = new ActionPaste(this);
			break;

		case DEL:
			pAct = new ActionDelete(this);
			break;

		case DSN_MODE:
			if (this->TempSelectedComponentId >= 0 && dynamic_cast<Module*>(Temp_CompList[this->TempSelectedComponentId])) RevertTemp();
			pAct = new ActionDsnWindow(this);
			break;

		case MOD_MODE:
			pAct = new ActionModWindow(this);
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

		case UNDO:
			pAct = new ActionUndo(this);
			break;

		case REDO:
			pAct = new ActionRedo(this);
			break;
		case LOG:
			pAct = new ActionCircuitLog(this);
			break;
		case CURR_MEASURE:
			pAct = new ActionMeasureCurrent(this);
			break;
		case VOLT_MEASURE:
			pAct = new ActionMeasureVoltage(this);
			break;
		case EXIT:
			pAct = new ActionExit(this);
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		if (ActType != REDO && 
			ActType != UNDO &&
			ActType != SELECT &&
			ActType != SIM_MODE &&
			ActType != DSN_MODE &&
			ActType != MOD_MODE && pUI->getAppMode() == DESIGN) this->SaveActionToStack(pAct);
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
	while (!this->ActionsRedoStack.empty()) delete ActionsRedoStack.top(), ActionsRedoStack.pop(); // Clearing the Redo Stack Objects from memory
	while (!this->ActionsUndoStack.empty()) delete ActionsUndoStack.top(), ActionsUndoStack.pop(); // Clearing the Undo Stack Objects from memory

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

void ApplicationManager::GetTempComponentList(Component* CompListNew[]) {
	for (int i = 0; i < MaxCompCount; i++) {
		CompListNew[i] = Temp_CompList[i];
	}
}

void ApplicationManager::GetTempConnectionList(Connection* ConnListNew[]) {
	for (int i = 0; i < MaxConnCount; i++) {
		ConnListNew[i] = Temp_ConnList[i];
	}
}

bool ApplicationManager::isGround(Component* c) const {
	return (c->GetItemType() == "GND");
	//if (c->GetItemType() == "GND") return true;
	//else return false;
}

bool ApplicationManager::isSwitch(Component* c) const {
	return (c->GetItemType() == "SWT");
	//if (c->GetItemType() == "SWT") return true;
	//else return false;
}

double ApplicationManager::getCompValue(Component* component) {

		return component->getValue();
}

string ApplicationManager::getCompLabel(Component* component) {

	return component->getLabel();
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

void ApplicationManager::CloneSelectedComponent() {

	Component* SelectedComponent = CompList[getSelectedComponentId()];
	string compType = SelectedComponent->GetItemType();
	GraphicsInfo* pGInfo = new GraphicsInfo(2);
	
	if (compType == "RES") ComponentClone = new Resistor(pGInfo);
	else if (compType == "BLB") ComponentClone = new Bulb(pGInfo);
	else if (compType == "BAT") ComponentClone = new Battery(pGInfo);
	else if (compType == "SWT") ComponentClone = new Switch(pGInfo);
	else if (compType == "GND") ComponentClone = new Ground(pGInfo);
	else if (compType == "BUZ") ComponentClone = new Buzzer(pGInfo);
	else if (compType == "FUS") ComponentClone = new Fuse(pGInfo);
	else ComponentClone = nullptr;

	if (ComponentClone) {
		ComponentClone->setLabel(SelectedComponent->getLabel());
		ComponentClone->setValue(SelectedComponent->getValue());
	}
}

Component* ApplicationManager::getClonedComponent() {
	return ComponentClone;
}


void ApplicationManager::ResetClonedComponent() {
	this->ComponentClone = nullptr;
}


void ApplicationManager::deleteSelectedComponent() {
	for (int i = 0, k = 0; i < MaxCompCount; i++) {
		if (CompList[i] == nullptr || !CompList[i]->isClicked()) {
			CompList[k] = CompList[i];
			k++;
		}
		else {
			delete CompList[i];
			CompList[i] = nullptr;
			pUI->ClearStatusBar();
			CompCount--;
		}
	}

	/// TODO: remove connections+
	pUI->ClearDrawingArea();
	pUI->CreateDrawingArea();
	UpdateInterface();
}


/*///////////////////////////////////////////
				UNDO & REDO
///////////////////////////////////////////*/

void ApplicationManager::Undo() {
	if (this->ActionsUndoStack.empty()) {
		pUI->PrintMsg("Undo Stack is Empty");
		return;
	}

	Action* UndoStackTopElement = this->ActionsUndoStack.top();
	UndoStackTopElement->Undo();
	this->ActionsRedoStack.push(UndoStackTopElement);
	this->ActionsUndoStack.pop();

	pUI->PrintMsg("Action Reversed!");
}

void ApplicationManager::Redo() {
	if (this->ActionsRedoStack.empty()) {
		pUI->PrintMsg("Redo Stack is Empty");
		return;
	}

	Action* RedoStackTopElement = this->ActionsRedoStack.top();
	RedoStackTopElement->Redo();
	this->ActionsUndoStack.push(RedoStackTopElement);
	this->ActionsRedoStack.pop();

	pUI->PrintMsg("Action Recovered!");
}

void ApplicationManager::SaveActionToStack(Action* act) {
	this->ActionsUndoStack.push(act);
}


bool ApplicationManager::isCircuitClosed() const
{
	if (CircuitTotalCurrent > MaxCurrent) {
		return false;
	}
	
	for (int i = 0; i < MaxCompCount; i++) {
		if (CompList[i] != nullptr) {
			if ((CompList[i]->GetItemType() == "SWT")) {
				if(CompList[i]->isClosed() == false)
					return false;
			}
		}
	}
	
	return true;
}

void ApplicationManager::updateCircuitState()
{
	bool state = isCircuitClosed();
	updateTotalVoltage();
	updateTotalResistance();
	updateTotalCurrent();
	
	state = isCircuitClosed();
	bool exceeded_limit = false;
	if (CircuitTotalCurrent > MaxCurrent) {
		exceeded_limit = true;
	}

	for (int i = 0; i < MaxCompCount; i++) {
		if ((CompList[i] != nullptr)) {
			if (CompList[i]->GetItemType() != "SWT") {
				CompList[i]->setClosed(state);
				CompList[i]->setExceededLimit(exceeded_limit);
				if (state) {
					if (CompList[i]->GetItemType() == "BUZ") {
						PlaySound(TEXT("buzzer_sound.wav"),0,SND_ASYNC);
					}
				}
			}
		}
	}

	
}

void ApplicationManager::updateTotalVoltage()
{
	CircuitTotalVoltage = 0;
	for (int i = 0; i < MaxCompCount; i++) {
		if (CompList[i] != nullptr) {
			if (CompList[i]->GetItemType() == "BAT") {
				CircuitTotalVoltage += CompList[i]->getValue();
			}
		}
	}
}

void ApplicationManager::updateTotalCurrent()
{
	if (!isCircuitClosed()) {
		CircuitTotalCurrent = 0;
	}
	else {
		CircuitTotalCurrent = CircuitTotalVoltage / CircuitTotalResistance;
	}
}

double ApplicationManager::getTotalVoltage() const
{
	return CircuitTotalVoltage;
}

double ApplicationManager::getTotalCurrent() const
{
	return CircuitTotalCurrent;
}

double ApplicationManager::getTotalResistance() const
{
	return CircuitTotalResistance;
}

int ApplicationManager::getComponent(int x, int y) const
{
	GraphicsInfo* CompListGraphicsInfo = new GraphicsInfo(2);
	for (int i = 0; i < MaxCompCount; i++) {
		// If there is a component inside the drawing area, proceed
		if (CompList[i] != nullptr) {
			// Gets the graphical info of component [i]
			CompListGraphicsInfo = CompList[i]->getGraphicsInfo();
			// If the x & y of the mouse lies within the area of the component, make it highlighted and display its information
			if (x >= CompListGraphicsInfo->PointsList[0].x && x <= CompListGraphicsInfo->PointsList[1].x && y >= CompListGraphicsInfo->PointsList[0].y && y <= CompListGraphicsInfo->PointsList[1].y) {
				CompList[i]->setClick(true); // setClick(true) makes drawResistor use the highlighted image
				return i;
			}
		}
	}
	return -1;
}

void ApplicationManager::updateTotalResistance()
{
	CircuitTotalResistance = 0;
	string comptype;
	for (int i = 0; i < MaxCompCount; i++) {
		if (CompList[i] != nullptr) {
			comptype = CompList[i]->GetItemType();
			if ((comptype != "SWT") && (comptype != "GND") && (comptype != "BAT") ) {
				CircuitTotalResistance += CompList[i]->getValue();
			}
		}
	}
}




void ApplicationManager::MakeCompNull(Component* comp) {
	bool found = 0;
	for (int i = 0; i < MaxCompCount; i++) {
		if (CompList[i] == comp) {
			CompList[i] = nullptr;
			found = 1;
		}
		if (found && i + 1 != MaxCompCount) {
			CompList[i] = CompList[i + 1];
		}
	}
	CompCount--;

	/// TODO: remove connections+
	pUI->ClearDrawingArea();
	pUI->CreateDrawingArea();
	UpdateInterface();
}

void ApplicationManager::MakeConnNull(Connection* conn) {
	bool found = 0;
	for (int i = 0; i < MaxConnCount; i++) {
		if (ConnList[i] == nullptr) {
			break;
		}
		if (ConnList[i] == conn) {
			ConnList[i] = nullptr;
			found = 1;
		}
		if (found && i + 1 != MaxConnCount) {
			ConnList[i] = ConnList[i + 1];
		}
	}
	int detectedComponents = 0;
	for (int i = 0; i < MaxCompCount; i++) {
		if (CompList[i] == nullptr || detectedComponents == 2) {
			break;
		}
		if (CompList[i]->getTerm1Conn() == conn) {
			detectedComponents += 1;
			CompList[i]->setTerm1Conn(nullptr);
		}
		if (CompList[i]->getTerm2Conn() == conn) {
			detectedComponents += 1;
			CompList[i]->setTerm2Conn(nullptr);
		}
	}
	ConnCount--;

	/// TODO: remove connections+
	pUI->ClearDrawingArea();
	pUI->CreateDrawingArea();
	UpdateInterface();
}



// Restoring the connection between the associated components
void ApplicationManager::RestoreConnection(Connection* conn) {
	Component* Comp1 = conn->getComp1();
	Component* Comp2 = conn->getComp2();

	ConnectionInfo* connInfo = conn->getConnInfo();

	// Connect to the correct terminals

	switch (connInfo->item1_terminal) {
	case 0:
		Comp1->setTerm1Conn(conn);
		break;
	case 1:
		Comp1->setTerm2Conn(conn);
		break;
	}

	switch (connInfo->item2_terminal) {
	case 0:
		Comp2->setTerm1Conn(conn);
		break;
	case 1:
		Comp2->setTerm2Conn(conn);
		break;
	}

	this->AddConnection(conn);
}

void ApplicationManager::CreateTemp() {
	Temp_CompCount = CompCount;
	Temp_ConnCount = ConnCount;
	GetComponentList(Temp_CompList);
	GetConnectionList(Temp_ConnList);

	EmptyData();

	Temp_CompList[this->SelectedComponentId]->GetCompList(CompList);
	Temp_CompList[this->SelectedComponentId]->GetConnList(ConnList);
	CompCount = Temp_CompList[this->SelectedComponentId]->GetCompCount();
	ConnCount = Temp_CompList[this->SelectedComponentId]->GetConnCount();

	this->TempSelectedComponentId = this->SelectedComponentId;
}

void ApplicationManager::RevertTemp() {
	this->SelectedComponentId = this->TempSelectedComponentId;

	Temp_CompList[this->SelectedComponentId]->SetCompList(CompList);
	Temp_CompList[this->SelectedComponentId]->SetConnList(ConnList);
	Temp_CompList[this->SelectedComponentId]->SetCompCount(CompCount);
	Temp_CompList[this->SelectedComponentId]->SetConnCount(ConnCount);

	CompCount = Temp_CompCount;
	ConnCount = Temp_ConnCount;
	GetTempComponentList(CompList);
	GetTempConnectionList(ConnList);

	EmptyTempData();
}