#include "Connection.h"

Connection::Connection(GraphicsInfo *r_GfxInfo, Component *cmp1, Component *cmp2)
{
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