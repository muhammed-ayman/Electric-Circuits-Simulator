#include "Connection.h"
#include <iostream>
Connection::Connection(ConnectionInfo *CInfo, GraphicsInfo *r_GfxInfo, Component *cmp1, Component *cmp2)
{
	*cInfo = *CInfo;
	pGfxInfo = r_GfxInfo;
	Cmpnt1 = cmp1;
	Cmpnt2 = cmp2;
}

Connection::Connection() {

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

void Connection::setClick(bool clickStatus) {
	pGfxInfo->isClicked = clickStatus;
}

GraphicsInfo* Connection::getGraphicsInfo() const {
	return this->pGfxInfo;
}

void Connection::Save(ofstream& saveFile, string id)
{	
	saveFile << to_string(cInfo->component1+1) + ", ";
	saveFile << to_string(cInfo->component2+1) + ", ";
	saveFile << to_string(cInfo->item1_terminal) + ", ";
	saveFile << to_string(cInfo->item2_terminal) + "\n";
}