#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "UI\UI.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include "Components\Connection.h"
#include <stack>



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
	int GroundCount = 0;
	
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)
	Connection* ConnList[MaxConnCount]; // List of all Connections (Array of pointers)

	UI* pUI; //pointer to the UI

	int SelectedComponentId = -1; //initial value for selected component ID
	int SelectedConnectionId = -1; //initial value for selected connection ID

	Component* ComponentClone = nullptr;

	// Undo & Redo Stacks
	stack<Action*> ActionsRedoStack;
	stack<Action*> ActionsUndoStack;

	//calculations variables
	double CircuitTotalVoltage = 0;
	double CircuitTotalCurrent = 0;
	double CircuitTotalResistance = 0;
	

public:	
	ApplicationManager(); //constructor

	void ResetData();

	int GetGroundCount();

	bool isGround(Component* c) const;

	bool isSwitch(Component* c) const;
	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	
	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to UI Object
	UI* GetUI();
	

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	//Retrieves the current list of added components. 	
	void GetComponentList(Component* CompListNew[]);
	void GetConnectionList(Connection* ConnListNew[]);

	int GetComponentCount();
	int GetConnectionCount();

	void setSelectedComponentId(int selectedCompId); // setter for selected component ID
	int getSelectedComponentId(); // getter for selected component ID

	void setSelectedConnectionId(int selectedConnId); // setter for selected connection ID
	int getSelectedConnectionId(); // getter for selected connection ID

	// Adds a new connection to the list of connections
	void AddConnection(Connection* pConn);

	double getCompValue(Component* component);

	string getCompLabel(Component* component);

	// Retrieves the current list of added connections. 	
	

	// Load Circuit
	void LoadCircuit(string*** parsedData, int comCount, int conCount);

	// Copy, Cut, and Paste
	void CloneSelectedComponent();
	Component* getClonedComponent();
	void ResetClonedComponent();

	void ReduceCompCountByOne();


	void deleteSelectedComponent();

	// Redo & Undo Related Methods
	void Undo();
	void Redo();
	void SaveActionToStack(Action* act);
	void MakeCompNull(Component* comp);

	//closing/opening circuit part
	bool isCircuitClosed() const;
	void updateCircuitState();


	//functions for circuit variables calculations
	void updateTotalVoltage();
	void updateTotalCurrent();
	void updateTotalResistance();
	//getters for circuit variables
	double getTotalVoltage() const;
	double getTotalCurrent() const;
	double getTotalResistance() const;


	//function for getting the id of the component based on its x,y coordinates
	int getComponent(int x, int y) const;

	// test
	void deleteComponent(Component* Comp);



	//destructor
	~ApplicationManager();
};

#endif