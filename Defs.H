#ifndef CONST_H
#define CONST_H

//This header file contains some defenitions to be used all over the application

//All possible actions
enum ActionType
{
	ADD_RESISTOR,		//Add a resistor
	ADD_BULB,			//Add Bulb
	ADD_BATTERY,		//Add Battery
	ADD_SWITCH,			//Add Switch
	ADD_GROUND,			//Add Ground
	ADD_BUZZER,			//Add Buzzer
	ADD_FUSE,			//Add Fuse
	ADD_MODULE,			//Add Module
	ADD_CONNECTION,		//Add Wire Connection

	ADD_Label,			//Add Label to a Component, a Connection
	EDIT_Label,			//Edit Label of a Component, a Connection

	ADD_Value,			// Add Value to a Component, a Connection
	EDIT_Value,			// Edit Value to a Component, a Connection

	Change_Switch,		//Change Switch Status in Simulation Mode

	SELECT,		//Select a Component, a Connection
	DEL,		//Delete a Component, a Connection
	MOVE,		//Move a Component, a Connection

	SAVE,		//Save the whole Circuit to a file
	LOAD,		//Load a Circuit from a file

	UNDO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled

	DSN_MODE,	//Switch to Design mode
	SIM_MODE,	//Switch to Simulatiom mode
	MOD_MODE,

	EXIT,		//Exit the application

	STATUS_BAR,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar

};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION,
	MODULE
};

enum Items // All possible items
{
	RES,
	BLB,
	BAT,
	SWT,
	GND,
	BUZ,
	FUS,
	MOD,
	CON
};

struct ConnectionInfo
{
	int component1 = -1;
	int component2 = -1;

	//to indicate which side to be connected up = 0 ,down = 1
	int item1_terminal = 0;
	int item2_terminal = 0;
};



//Maximum number of connections that can be connected to any output components
#define MAX_CONNS 20

#define MaxCompCount 200
#define MaxConnCount 400


#endif