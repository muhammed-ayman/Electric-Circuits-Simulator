#include "ActionAddConn.h"
#include "../ApplicationManager.h"


ActionAddConn::ActionAddConn(ApplicationManager* pApp) :Action(pApp)
{
	pManager->GetComponentList(CompList);
}

ActionAddConn::~ActionAddConn(void)
{
}

/// <summary>
/// returns the index of the component whose coordinates clicked on if found and returns -1 otherwise
/// </summary>
/// <param name="x"> x coordinate last clicked</param>
/// <param name="y"> y coordinate last clicked</param>
/// <returns></returns>
int ActionAddConn::getComponent(int x, int y)
{
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

void ActionAddConn::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();	

	if (!pUI->getWriteMode()) {
		pUI->PrintMsg("You can not perform this action");
		return;
	}
	
	pUI->PrintMsg("Select two components");
	
	int x = 0, y = 0;

	// Retrieves the mouse coordinates clicked by the user
	pUI->GetPointClicked(x,y);


	cInfo->component1 = getComponent(x,y);


	if (cInfo->component1 == -1) { pUI->PrintMsg("Nothing selected"); }
	
	else {
		pUI->PrintMsg("Component 1 selected");
		comp1_graph_info = CompList[cInfo->component1]->getGraphicsInfo();

		if (x >= comp1_graph_info->PointsList[0].x && x <= comp1_graph_info->PointsList[0].x + 50) {
			cInfo->item1_terminal = 0;
		}
		else {
			cInfo->item1_terminal = 1;
		}

		//checking if the first selected component is connected at the selected terminal
		if (((cInfo->item1_terminal == 0) && (CompList[cInfo->component1]->getTerm1Conn() != nullptr))) {
			pUI->PrintMsg("First component is already connected at left terminal");
		}
		else if (((cInfo->item1_terminal == 1) && (CompList[cInfo->component1]->getTerm2Conn() != nullptr))) {
			pUI->PrintMsg("First component is already connected at right terminal");

		}
		else {

			pUI->GetPointClicked(x, y);



			cInfo->component2 = getComponent(x, y);

			if (cInfo->component2 == -1) {
				pUI->PrintMsg("Nothing selected to connect to!");
				CompList[cInfo->component1]->setClick(false);
			}
			else if (cInfo->component2 == cInfo->component1) {
				pUI->PrintMsg("Cannot connect a component to itself!");

			}
			else {
				pUI->PrintMsg("Second component selected");

				comp2_graph_info = CompList[cInfo->component2]->getGraphicsInfo();

				if (x >= comp2_graph_info->PointsList[0].x && x <= comp2_graph_info->PointsList[0].x + 50) {
					cInfo->item2_terminal = 0;
				}
				else {
					cInfo->item2_terminal = 1;
				}

				//checking if the second component is connected at the selected terminal 
				if (((cInfo->item2_terminal == 0) && (CompList[cInfo->component2]->getTerm1Conn() != nullptr))) {
					pUI->PrintMsg("Second component is already connected at left terminal");

				}
				else if (((cInfo->item2_terminal == 1) && (CompList[cInfo->component2]->getTerm2Conn() != nullptr))) {
					pUI->PrintMsg("Second component is already connected at right terminal");
				}
				else {
					ProcessConnection(cInfo);
				}

			}
		}
	}
}

void ActionAddConn::ProcessConnection(ConnectionInfo* cInfo) {
	comp1_graph_info = CompList[cInfo->component1]->getGraphicsInfo();
	comp2_graph_info = CompList[cInfo->component2]->getGraphicsInfo();


	if (cInfo->item1_terminal == 0) {
		conn_graph_info->PointsList[0].x = comp1_graph_info->PointsList[0].x+5;
		conn_graph_info->PointsList[0].y = comp1_graph_info->PointsList[0].y+50;

	}
	else {
		conn_graph_info->PointsList[0].x = comp1_graph_info->PointsList[0].x+95;
		conn_graph_info->PointsList[0].y = comp1_graph_info->PointsList[0].y+50;
	}

	if (cInfo->item2_terminal == 0) {
		conn_graph_info->PointsList[1].x = comp2_graph_info->PointsList[0].x+5;
		conn_graph_info->PointsList[1].y = comp2_graph_info->PointsList[0].y + 50;

	}
	else {
		conn_graph_info->PointsList[1].x = comp2_graph_info->PointsList[0].x+95;
		conn_graph_info->PointsList[1].y = comp2_graph_info->PointsList[0].y+50;
	}
	
	conn = new Connection(cInfo, conn_graph_info, CompList[cInfo->component1], CompList[cInfo->component2]);


	if (cInfo->item1_terminal == 0) {
		CompList[cInfo->component1]->setTerm1Conn(conn);
	}
	else {
		CompList[cInfo->component1]->setTerm2Conn(conn);
	}

	if (cInfo->item2_terminal == 0) {
		CompList[cInfo->component2]->setTerm1Conn(conn);
	}
	else {
		CompList[cInfo->component2]->setTerm2Conn(conn);
	}

	pManager->AddConnection(conn);
}


void ActionAddConn::Undo()
{
	pManager->MakeConnNull(this->conn);

}

void ActionAddConn::Redo()
{
	pManager->RestoreConnection(this->conn);
}

