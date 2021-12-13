#include "ActionAddConn.h"
#include "../ApplicationManager.h"
#include <iostream>
using namespace std;

ActionAddConn::ActionAddConn(ApplicationManager* pApp) :Action(pApp)
{
	pManager->GetComponentList(CompList);
}

ActionAddConn::~ActionAddConn(void)
{
}

void ActionAddConn::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();	
	
	pUI->PrintMsg("Select two components");
	
	int x = 0, y = 0;

	// Retrieves the mouse coordinates clicked by the user
	pUI->GetPointClicked(x,y);


	// Looping over the list of components (max = 200)
	for (int i = 0; i < 200; i++) {
		// If there is a component inside the drawing area, proceed
		if (CompList[i] != nullptr) {
			// Gets the graphical info of component [i]
			GraphicsInfo* CompListGraphicsInfo = CompList[i]->getGraphicsInfo();
			// If the x & y of the mouse lies within the area of the component, make it highlighted and display its information
			if (x >= CompListGraphicsInfo->PointsList[0].x && x <= CompListGraphicsInfo->PointsList[1].x && y >= CompListGraphicsInfo->PointsList[0].y && y <= CompListGraphicsInfo->PointsList[1].y) {
				CompList[i]->setClick(true); // setClick(true) makes drawResistor use the highlighted image
				cInfo->component1 = i;
			}
		}
	}


	if (cInfo->component1 == -1) { pUI->PrintMsg("Nothing selected"); }
	else {
		pUI->PrintMsg("Component 1 selected");
		GraphicsInfo* comp1_graph_info = CompList[cInfo->component1]->getGraphicsInfo();
		if (y >= comp1_graph_info->PointsList[0].y && y <= comp1_graph_info->PointsList[0].y + 50) {
			cInfo->item1_terminal = 0;
		}
		else {
			cInfo->item1_terminal = 1;
		}

		pUI->GetPointClicked(x, y);


		for (int i = 0; i < 200; i++) {
			// If there is a component inside the drawing area, proceed
			if (CompList[i] != nullptr) {
				// Gets the graphical info of component [i]
				GraphicsInfo* CompListGraphicsInfo = CompList[i]->getGraphicsInfo();
				// If the x & y of the mouse lies within the area of the component, make it highlighted and display its information
				if (x >= CompListGraphicsInfo->PointsList[0].x && x <= CompListGraphicsInfo->PointsList[1].x && y >= CompListGraphicsInfo->PointsList[0].y && y <= CompListGraphicsInfo->PointsList[1].y) {
					CompList[i]->setClick(true); // setClick(true) makes drawResistor use the highlighted image
					cInfo->component2 = i;
				}
			}
		}
		if (cInfo->component2 == -1) {
			pUI->PrintMsg("Nothing selected to connect to!");
			CompList[cInfo->component1]->setClick(false);
		}
		else if (cInfo->component2 == cInfo->component1) {
			pUI->PrintMsg("Cannot connect a component to itself!");

		}
		else {
			pUI->PrintMsg("Component two selected");

			GraphicsInfo* comp2_graph_info = CompList[cInfo->component2]->getGraphicsInfo();

			if (y >= comp2_graph_info->PointsList[0].y && y <= comp2_graph_info->PointsList[0].y + 50) {
				cInfo->item2_terminal = 0;
			}
			else {
				cInfo->item2_terminal = 1;
			}

			ProcessConnection(cInfo);
		}
	}
}

void ActionAddConn::ProcessConnection(ConnectionInfo* cInfo) {
	GraphicsInfo* comp1_graph_info = CompList[cInfo->component1]->getGraphicsInfo();
	GraphicsInfo* comp2_graph_info = CompList[cInfo->component2]->getGraphicsInfo();

	if (cInfo->item1_terminal == 0) {
		conn_graph_info->PointsList[0].x = comp1_graph_info->PointsList[0].x + 50;
		conn_graph_info->PointsList[0].y = comp1_graph_info->PointsList[0].y;

	}
	else {
		conn_graph_info->PointsList[0].x = comp1_graph_info->PointsList[1].x - 50;
		conn_graph_info->PointsList[0].y = comp1_graph_info->PointsList[1].y;
	}

	if (cInfo->item2_terminal == 0) {
		conn_graph_info->PointsList[1].x = comp2_graph_info->PointsList[0].x + 50;
		conn_graph_info->PointsList[1].y = comp2_graph_info->PointsList[0].y + 5;

	}
	else {
		conn_graph_info->PointsList[1].x = comp2_graph_info->PointsList[1].x - 50;
		conn_graph_info->PointsList[1].y = comp2_graph_info->PointsList[1].y - 5;
	}
	
	Connection* conn = new Connection(cInfo, conn_graph_info, CompList[cInfo->component1], CompList[cInfo->component2]);

	if (cInfo->item1_terminal == 0) {
		CompList[cInfo->component1]->setTerm1Conn(conn);
	}
	else {
		CompList[cInfo->component1]->setTerm2Conn(conn);
	}

	if (cInfo->item2_terminal == 0) {
		CompList[cInfo->component1]->setTerm1Conn(conn);
	}
	else {
		CompList[cInfo->component1]->setTerm2Conn(conn);
	}

	pManager->AddConnection(conn);
}


void ActionAddConn::Undo()
{}

void ActionAddConn::Redo()
{}

