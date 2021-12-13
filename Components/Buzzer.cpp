#include "Buzzer.h"

Buzzer::Buzzer(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{
	this->itemType = BUZ;
}

void Buzzer::Draw(UI* pUI)
{
	//Call output class and pass buzzer drawing info to it.
	pUI->DrawBuzzer(*m_pGfxInfo); //update to draw buzzer

}

void Buzzer::Operate()
{

}

string* Buzzer::Save()
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