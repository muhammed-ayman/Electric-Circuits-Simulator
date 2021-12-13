#include "Ground.h"

Ground::Ground(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{
	this->itemType = GND;
}

void Ground::Draw(UI* pUI)
{
	//Call output class and pass ground drawing info to it.
	pUI->DrawGround(*m_pGfxInfo); //update to draw ground

}

void Ground::Operate()
{

}

string* Ground::Save()
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