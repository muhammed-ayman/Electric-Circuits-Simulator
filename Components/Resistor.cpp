#include "Resistor.h"

Resistor::Resistor(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{
	this->itemType = RES;
}

void Resistor::Draw(UI* pUI)
{
	//Call output class and pass resistor drawing info to it.
	pUI->DrawResistor(*m_pGfxInfo); //update to draw resistor

}

void Resistor::Operate()
{

}

string* Resistor::Save()
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