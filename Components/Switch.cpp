#include "Switch.h"

Switch::Switch(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{
	this->itemType = SWT;
	//r_GfxInfo->closed = false;
	
}

void Switch::Draw(UI* pUI)
{
	//Call output class and pass switch drawing info to it.
	pUI->DrawSwitch(*m_pGfxInfo); //update to draw switch

}



void Switch::Operate()
{

}

string* Switch::Save()
{
	GraphicsInfo* gInfo = getGraphicsInfo();
	string* data = new string[6];

	data[0] = GetItemType();
	data[2] = getLabel();
	data[3] = to_string(getValue());
	data[4] = to_string(gInfo->PointsList[0].x);
	data[5] = to_string(gInfo->PointsList[0].y);

	return data;
}




