#include "Switch.h"

Switch::Switch(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{
	this->itemType = SWT;
}

Switch::Switch() {

}

void Switch::Draw(UI* pUI)
{
	//Call output class and pass switch drawing info to it.
	pUI->DrawSwitch(*m_pGfxInfo); //update to draw switch

}

void Switch::Operate()
{

}

void Switch::Save(ofstream& saveFile, string id)
{
	GraphicsInfo* gInfo = getGraphicsInfo();

	saveFile << "SWT, ";
	saveFile << id + ", ";
	saveFile << getLabel() + ", ";
	saveFile << to_string(getValue()) + ", ";
	saveFile << to_string(gInfo->PointsList[0].x) + ", ";
	saveFile << to_string(gInfo->PointsList[0].y) + "\n";
}

void Switch::Load(GraphicsInfo* r_GfxInfo, string label, double value) {
	this->m_pGfxInfo = r_GfxInfo;
	this->m_Label = label;
	this->value = value;
}