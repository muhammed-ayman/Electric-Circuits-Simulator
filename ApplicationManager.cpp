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

		case EXIT:
			pAct = new ActionExit(this);
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		if (ActType != REDO && 
			ActType != UNDO &&
			ActType != SELECT) this->SaveActionToStack(pAct);
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