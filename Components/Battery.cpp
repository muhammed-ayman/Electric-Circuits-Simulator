#include "Battery.h"

Battery::Battery(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{
	this->itemType = BAT;
}

Battery::Battery() {

}

void Battery::Draw(UI* pUI)
{
	//Call output class and pass battery drawing info to it.
	pUI->DrawBattery(*m_pGfxInfo); //update to draw battery

}

void Battery::Operate()
{

}

void Battery::Save(ofstream& saveFile, string id)
{
	GraphicsInfo* gInfo = getGraphicsInfo();

	saveFile << "BAT, ";
	saveFile << id + ", ";
	saveFile << getLabel() + ", ";
	saveFile << to_string(getValue()) + ", ";
	saveFile << to_string(gInfo->PointsList[0].x) + ", ";
	saveFile << to_string(gInfo->PointsList[0].y) + "\n";
}

void Battery::Load(GraphicsInfo* r_GfxInfo, string label, double value) {
	this->m_pGfxInfo = r_GfxInfo;
	this->m_Label = label;
	this->value = value;
}