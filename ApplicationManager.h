#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "UI\UI.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include "Components\Connection.h"

// fix this later
#include <iostream>
#include <fstream>
#include <cstdlib>
using std::cerr;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::basic_ofstream;



//Main class that manages everything in the application.
class ApplicationManager
{

private:
	int CompCount;		//Actual number of Components
	int ConnCount;		//Actual number of Connections

	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)
	Connection* ConnList[MaxConnCount]; // List of all Connections (Array of pointers)

	ConnectionInfo* cInfo = new ConnectionInfo;

	UI* pUI; //pointer to the UI

	int SelectedComponentId = -1; //initial value for selected component ID
	

public:


public:	
	ApplicationManager(); //constructor

	void ResetData();

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	
	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to UI Object
	UI* GetUI();
	

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	//destructor
	~ApplicationManager();

	//Retrieves the current list of added components. 	
	void GetComponentList(Component* CompListNew[]);

	void setSelectedComponentId(int selectedCompId); // setter for selected component ID
	int getSelectedComponentId(); // getter for selected component ID

	// Adds a new connection to the list of connections
	void AddConnection(Connection* pConn);

	// Retrieves the current list of added connections. 	
	void GetConnectionList(Connection* ConnListNew[]);

	// Save Circuit
	void SaveCircuit(ofstream& saveFile);

	// Load Circuit
	void LoadCircuit(string*** parsedData, int comCount, int conCount);
};

#endif