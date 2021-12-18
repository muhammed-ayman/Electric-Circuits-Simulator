#include "Connection.h"
#include <iostream>
Connection::Connection(ConnectionInfo *CInfo, GraphicsInfo *r_GfxInfo, Component *cmp1, Component *cmp2)
{
	*cInfo = *CInfo;
	pGfxInfo = r_GfxInfo;
	Cmpnt1 = cmp1;
	Cmpnt2 = cmp2;
}

Connection::~Connection()
{
	delete[] conDataIn;
}

void Connection::Draw(UI* pUI)
{
	pUI->DrawConnection(*pGfxInfo);
}

string Connection::getConnectionLabel() const {
	return this->c_Label;
}

void Connection::setConnectionLabel(string label) {
	this->c_Label = label;
}


GraphicsInfo* Connection::getGraphicsInfo() const {
	return this->pGfxInfo;
}

string* Connection::Save()
{	
	conDataIn[0] = to_string(cInfo->component1+1);
	conDataIn[1] = to_string(cInfo->component2+1);
	conDataIn[2] = to_string(cInfo->item1_terminal);
	conDataIn[3] = to_string(cInfo->item2_terminal);

	std::cout << to_string(cInfo->component1 + 1) << "\n";
	return conDataIn;
}