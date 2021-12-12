#include "ActionAddConn.h"
#include "../ApplicationManager.h"
#include "../Defs.H"
#include <iostream>
using namespace std;

ActionAddConn::ActionAddConn(ApplicationManager* pApp) :Action(pApp)
{
}


ActionAddConn::~ActionAddConn(void)
{
}

void ActionAddConn::Execute()
{


	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	Component* CompList[200];

	pManager->GetComponentList(CompList);
	
	pUI->PrintMsg("Select two components");
	
	int x = 0, y = 0;
	//to indicate which side to be connected up = 0 ,down = 1
	int component1 = -1;
	int component2 = -1;
	int item1_terminal = 0;
	int item2_terminal = 0;
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
				component1 = i;
			}
		}
	}


	if (component1 == -1) { pUI->PrintMsg("Nothing selected"); }
	else {
		pUI->PrintMsg("Component 1 selected");
		GraphicsInfo* comp1_graph_info = CompList[component1]->getGraphicsInfo();
		if (y >= comp1_graph_info->PointsList[0].y && y <= comp1_graph_info->PointsList[0].y + 50) {
			item1_terminal = 0;
		}
		else {
			item1_terminal = 1;
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
					component2 = i;
				}
			}
		}
		if (component2 == -1) { 
			pUI->PrintMsg("Nothing selected to connect to!");
			CompList[component1]->setClick(false);
		}
		else if (component2 == component1) {
			pUI->PrintMsg("Cannot connect a component to itself!");

		}
		else {
			pUI->PrintMsg("Component two selected");
			GraphicsInfo* comp2_graph_info = CompList[component2]->getGraphicsInfo();

			if (y >= comp2_graph_info->PointsList[0].y && y <= comp2_graph_info->PointsList[0].y + 50) {
				item2_terminal = 0;
			}
			else {
				item2_terminal = 1;
			}

			GraphicsInfo* conn_graph_info = new GraphicsInfo(2);
			if (item1_terminal == 0) {
				conn_graph_info->PointsList[0].x = comp1_graph_info->PointsList[0].x+50;
				conn_graph_info->PointsList[0].y= comp1_graph_info->PointsList[0].y;

			}
			else {
				conn_graph_info->PointsList[0].x = comp1_graph_info->PointsList[1].x-50;
				conn_graph_info->PointsList[0].y = comp1_graph_info->PointsList[1].y;
			}

			if (item2_terminal == 0) {
				conn_graph_info->PointsList[1].x = comp2_graph_info->PointsList[0].x+50;
				conn_graph_info->PointsList[1].y = comp2_graph_info->PointsList[0].y+5;

			}
			else {
				conn_graph_info->PointsList[1].x = comp2_graph_info->PointsList[1].x-50;
				conn_graph_info->PointsList[1].y = comp2_graph_info->PointsList[1].y-5;
			}

			Connection* conn = new Connection(conn_graph_info, CompList[component1], CompList[component2]);
			if (item1_terminal == 0) {
				CompList[component1]->setTerm1Conn(conn);
			}
			else {
				CompList[component1]->setTerm2Conn(conn);

			}

			if (item2_terminal == 0) {
				CompList[component1]->setTerm1Conn(conn);

			}
			else {
				CompList[component1]->setTerm2Conn(conn);

			}

			pManager->AddConnection(conn);

		}

	
	}
}




void ActionAddConn::Undo()
{}

void ActionAddConn::Redo()
{}

