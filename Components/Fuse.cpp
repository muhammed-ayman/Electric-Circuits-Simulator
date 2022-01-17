#include "Fuse.h"

Fuse::Fuse(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{
	this->itemType = FUS;
}

Fuse::Fuse() {

}

void Fuse::Draw(UI* pUI)
{
	//Call output class and pass fuse drawing info to it.
	pUI->DrawFuse(*m_pGfxInfo); //update to draw fuse

}

void Fuse::Operate()
{

}

void Fuse::Save(ofstream& saveFile, string id)
{
	GraphicsInfo* gInfo = getGraphicsInfo();

	saveFile << "FUS, ";
	saveFile << id + ", ";
	saveFile << getLabel() + ", ";
	saveFile << to_string(getValue()) + ", ";
	saveFile << to_string(gInfo->PointsList[0].x) + ", ";
	saveFile << to_string(gInfo->PointsList[0].y) + "\n";
}

void Fuse::Load(GraphicsInfo* r_GfxInfo, string label, double value) {
	this->m_pGfxInfo = r_GfxInfo;
	this->m_Label = label;
	this->value = value;
}