#include "Ground.h"

Ground::Ground(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{
	this->itemType = GND;
}

Ground::Ground() {

}

void Ground::Draw(UI* pUI)
{
	//Call output class and pass ground drawing info to it.
	pUI->DrawGround(*m_pGfxInfo); //update to draw ground

}

void Ground::Operate()
{

}

void Ground::Save(ofstream& saveFile, string id)
{
	GraphicsInfo* gInfo = getGraphicsInfo();

	saveFile << "GND, ";
	saveFile << id + ", ";
	saveFile << getLabel() + ", ";
	saveFile << to_string(getValue()) + ", ";
	saveFile << to_string(gInfo->PointsList[0].x) + ", ";
	saveFile << to_string(gInfo->PointsList[0].y) + "\n";
}

void Ground::Load(GraphicsInfo* r_GfxInfo, string label, double value) {
	this->m_pGfxInfo = r_GfxInfo;
	this->m_Label = label;
	this->value = value;
}