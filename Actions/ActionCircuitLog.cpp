#include "ActionCircuitLog.h"
#include "../ApplicationManager.h"
#include <string>
#include <iostream>
using namespace std;

ActionCircuitLog::ActionCircuitLog(ApplicationManager* pApp) :Action(pApp)
{
}

ActionCircuitLog::~ActionCircuitLog(void)
{
}

void ActionCircuitLog::Execute()
{
	UI* pUI = pManager->GetUI();
	string expression = "";
	expression = expression+"Resistance: "+to_string(pManager->getTotalResistance())+"    Current: "+ to_string(pManager->getTotalCurrent()) +"    Voltage: "+ to_string(pManager->getTotalVoltage());
	pUI->PrintMsg(expression);
}

void ActionCircuitLog::Undo()
{}

void ActionCircuitLog::Redo()
{}