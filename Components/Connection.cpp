#include "Connection.h"
#include <iostream>
Connection::Connection(ConnectionInfo *cInfo, GraphicsInfo *r_GfxInfo, Component *cmp1, Component *cmp2)
{
	this->cInfo = cInfo;
	pGfxInfo = r_GfxInfo;
	Cmpnt1 = cmp1;
	Cmpnt2 = cmp2;
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
	string* data = new string[4];

	data[0] = to_string(cInfo->component1+1);
	data[1] = to_string(cInfo->component2+1);
	data[2] = to_string(cInfo->item1_terminal);
	data[3] = to_string(cInfo->item2_terminal);

	return data;
}