#include "Buzzer.h"

Buzzer::Buzzer(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{
	this->itemType = BUZ;
}

Buzzer::Buzzer() {

}

void Buzzer::Draw(UI* pUI)
{
	//Call output class and pass buzzer drawing info to it.
	pUI->DrawBuzzer(*m_pGfxInfo); //update to draw buzzer

}

void Buzzer::Operate()
{

}

void Buzzer::Save(ofstream& saveFile, string id)
{
	GraphicsInfo* gInfo = getGraphicsInfo();

	saveFile << "BUZ, ";
	saveFile << id + ", ";
	saveFile << getLabel() + ", ";
	saveFile << to_string(getValue()) + ", ";
	saveFile << to_string(gInfo->PointsList[0].x) + ", ";
	saveFile << to_string(gInfo->PointsList[0].y) + "\n";
}

void Buzzer::Load(GraphicsInfo* r_GfxInfo, string label, double value) {
	this->m_pGfxInfo = r_GfxInfo;
	this->m_Label = label;
	this->value = value;
}