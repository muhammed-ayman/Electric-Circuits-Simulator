#include "ActionSimWindow.h"
#include "..\ApplicationManager.h"
#include "../Components/Component.h"
#include <iostream>
using namespace std;

ActionSimWindow::ActionSimWindow(ApplicationManager* pApp) :Action(pApp)
{
}

ActionSimWindow::~ActionSimWindow(void)
{
}

bool ActionSimWindow::ValidateOneCircuit() {
	Component* CompList[MaxCompCount];
	pManager->GetComponentList(CompList);
	Component* currentComp = CompList[0];

	// Get Terminal Connections of the Component
	// Connection* conn1 = Comp->getTerm1Conn();
	// Connection* conn2 = Comp->getTerm2Conn();

	//int comp1Terminal = 0; int comp2Terminal = 0;
	Component* comp1 = nullptr; 

	// Get the correct connection terminal
	int counter = 0;
	for (int i = 1; i < MaxCompCount; i++) {
		
		Connection* conn1 = CompList[i]->getTerm1Conn();
		Connection* conn2 = CompList[i]->getTerm2Conn();
		//Component* comp2 = nullptr;
		
		if (currentComp->getTerm1Conn() != nullptr && conn1 != nullptr && (currentComp == conn1->getComp1() || currentComp == conn1->getComp2())) {
			if (currentComp == conn1->getComp1()) comp1 = conn1->getComp2();
			if (currentComp == conn1->getComp2()) comp1 = conn1->getComp1();
			currentComp = comp1;
			counter++;
		}

		if (currentComp->getTerm2Conn() != nullptr && conn2 != nullptr && (currentComp == conn2->getComp1() || currentComp == conn2->getComp2() )) {
			if (currentComp == conn2->getComp1()) comp1 = conn2->getComp2();
			if (currentComp == conn2->getComp2()) comp1 = conn2->getComp1();
			currentComp = comp1;
			counter++;
		}

		if (currentComp == CompList[0] && counter != 0) break;
	}

	cout << counter;

	if (counter != pManager->GetConnectionCount()) return false;
	else return true;
	
}

bool ActionSimWindow::Validate() {
	int counter = 0;
	Component* CompList[MaxCompCount];
	pManager->GetComponentList(CompList);

	if (pManager->GetGroundCount() == 1 && (pManager->GetComponentCount() == pManager->GetConnectionCount())) {
		for (int i = 0; i < pManager->GetComponentCount(); i++) {
			if (CompList[i] != nullptr) {
				if (!(pManager->isGround(CompList[i])) && !(pManager->isSwitch(CompList[i]))) {
					if (pManager->getCompValue(CompList[i]) > double(0) && pManager->getCompLabel(CompList[i]) != "Component") counter++;
				}
				if (pManager->isSwitch(CompList[i])) {
					if ((pManager->getCompValue(CompList[i]) == double(0) && pManager->getCompLabel(CompList[i]) != "Component"))counter++;
				}
				if(pManager->isGround(CompList[i])) {
					if (pManager->getCompValue(CompList[i]) == double(0) && pManager->getCompLabel(CompList[i]) != "Component") counter++;
				}
			}
		}
	}
	if (counter == pManager->GetComponentCount() && pManager->GetComponentCount() != 0) return true;
	return false;
}

void ActionSimWindow::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	if (Validate()) {

		if (ValidateOneCircuit()) {
			// unselecting selected objects in simulation mode
			Component* CompList[MaxCompCount];
			pManager->GetComponentList(CompList);
			for (int i = 0; i < MaxCompCount; i++) {
				if (CompList[i] != nullptr) {
					CompList[i]->setClick(false);
				}
			}

			Connection* Connlist[MaxConnCount];
			pManager->GetConnectionList(Connlist);
			for (int i = 0; i < MaxConnCount; i++) {
				if (Connlist[i] != nullptr) {
					Connlist[i]->setClick(false);
				}
			}

			//calculting total resistance,voltage,current
			pManager->updateTotalResistance();

			//creating simulation toolbar
			pUI->CreateSimulationToolBar();
			pUI->CreateDrawingArea();
			//updating circuit parameters
			pManager->updateCircuitState();
			//Print Action Message
			pUI->PrintMsg("Simulation Mode Initialized");
		} else pUI->PrintMsg("Cannot draw more than one circuit!");
		
	}
	else{
		pUI->PrintMsg("Circuit is not valid! One circuit, one ground (val=0), and full connections, labels, & values! Switch = 0!");
	}
	
}

void ActionSimWindow::Undo()
{
}

void ActionSimWindow::Redo()
{
}
