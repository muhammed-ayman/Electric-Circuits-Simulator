#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\UI\UI.h"
#include "Connection.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
using std::cerr;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::basic_ofstream;

//Base class for all components (resistor, capacitor,....etc) .
class Component
{
private:
	bool clicked; // indicates if the component is clicked

protected:
	string m_Label = "Component1"; // Initial label for all components

	Items itemType; //Creating an instance of the Items enumerator.
	
	double value = 3; // Variable that holds the value of each component

	//Each component has two ending terminals (term1, term2)
	double term1_volt, term2_volt;	//voltage at terminals 1&2

	//Each terminal is connected to set of connections
	Connection* term_connections[2]; //list of pointers to connections

	int term1_conn_count;	//actual no. of connections to each terminal
	int term2_conn_count;


	GraphicsInfo *m_pGfxInfo;	//The parameters required to draw a component

public:
	Component(GraphicsInfo *r_GfxInfo);
	//void setTerm1Volt(double v);		//sets the voltage at terminal1
	//void setTerm2Volt(double v);		//sets the voltage at terminal2
	//double getTerm1Volt();				//returns the voltage at terminal1
	//double getTerm2Volt();				//returns the voltage at terminal2

	virtual void Operate() = 0;	//Calculates the output voltage according to the inputs
	virtual void Draw(UI* ) = 0;	//for each component to Draw itself
	virtual void Save(ofstream& saveFile, string id) = 0; //return save data of the component
	virtual void Load(GraphicsInfo* r_GfxInfo, string label, double value) = 0;
	
	//virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	//virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1

	//virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.

	
	Component();	
	
	//Destructor must be virtual
	virtual ~Component();

	// Gets graphical info of the component drawn
	GraphicsInfo* getGraphicsInfo();
	void setGraphicsInfo(GraphicsInfo* m_pGfxInfo);
	// changes the click of the mouse to true or false. Takes a boolean as a parameter and changes the mouse status as per the boolean
	void setClick(bool clickStatus);
	bool isClicked();

	//changes the state closed
	void setClosed(bool state);
	//gets the state closed from the graphics info
	bool isClosed() const;

	//changes the exceeded limit bool value
	void setExceededLimit(bool value);

	// Label Getter & Setter
	string getLabel() const;
	void setLabel(string label);

	// Value Getter & Setter
	double getValue() const;
	void setValue(double value);


	string GetItemType() const;

	//getter and setter for the component term1 connection
	Connection* getTerm1Conn() const;
	void setTerm1Conn(Connection *conn);

	//getter and setter for the component term1 connection
	Connection* getTerm2Conn() const;
	void setTerm2Conn(Connection *conn);


	// module virtuals
	virtual void SetCompList(Component* CompListNew[]){};
	virtual void SetConnList(Connection* CompListNew[]){};
	virtual void GetCompList(Component* CompListNew[]){};
	virtual void GetConnList(Connection* CompListNew[]){};
	virtual void SetCompCount(int CompCount){};
	virtual void SetConnCount(int ConnCount){};
	virtual int GetCompCount() { return 0; };
	virtual int GetConnCount() { return 0; };


};

#endif
