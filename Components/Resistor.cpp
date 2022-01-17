#include "Resistor.h"

Resistor::Resistor(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{
	this->itemType = RES;
}

Resistor::Resistor() {

}

void Resistor::Draw(UI* pUI)
{
	//Call output class and pass resistor drawing info to it.
	pUI->DrawResistor(*m_pGfxInfo); //update to draw resistor

}

void Resistor::Operate()
{

}

void Resistor::Save(ofstream& saveFile, string id)
{
	GraphicsInfo* gInfo = getGraphicsInfo();

	saveFile << "RES, ";
	saveFile << id + ", ";
	saveFile << getLabel() + ", ";
	saveFile << to_string(getValue()) + ", ";
	saveFile << to_string(gInfo->PointsList[0].x) + ", ";
	saveFile << to_string(gInfo->PointsList[0].y) + "\n";
}


void Resistor::Load(GraphicsInfo* r_GfxInfo, string label, double value){
	this->m_pGfxInfo = r_GfxInfo;
	this->m_Label = label;
	this->value = value;
}