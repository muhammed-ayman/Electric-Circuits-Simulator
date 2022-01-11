#pragma once
#include "../UI/UI.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
using std::cerr;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::basic_ofstream;


class Component;	//forward class declaration

class Connection 
{

private:
	string c_Label = "Connection"; // Initial value for connection
	//connection connects between two compoenets
	Component	*Cmpnt1, *Cmpnt2;
	GraphicsInfo *pGfxInfo = new GraphicsInfo(2);	//The parameters required to draw a connection
	ConnectionInfo* cInfo = new ConnectionInfo;
	string* conDataIn = new string[4];

public:
	Connection(ConnectionInfo *cInfo, GraphicsInfo *r_GfxInfo, Component *cmp1=nullptr, Component *cmp2=nullptr);
	Connection();
	~Connection();
	virtual void Draw(UI* );	//for connection to Draw itself
	virtual void Save(ofstream& saveFile, string id); //returns components data to save
	//virtual void Save(ofstream& saveFile);
	string getConnectionLabel() const;
	void setConnectionLabel(string label);
	void setClick(bool clickStatus);

	GraphicsInfo* getGraphicsInfo() const;

};
