#pragma once
#include "../UI/UI.h"

class Component;	//forward class declaration

class Connection 
{

private:
	string c_Label = "Connection"; // Initial value for connection
	//connection connects between two compoenets
	Component	*Cmpnt1, *Cmpnt2;
	GraphicsInfo *pGfxInfo;	//The parameters required to draw a connection

public:
	Connection(GraphicsInfo *r_GfxInfo, Component *cmp1=nullptr, Component *cmp2=nullptr);

	virtual void Draw(UI* );	//for connection to Draw itself
	string getConnectionLabel() const;
	void setConnectionLabel(string label);

};
