#include "Fuse.h"

Fuse::Fuse(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{
	this->itemType = FUS;
}

void Fuse::Draw(UI* pUI)
{
	//Call output class and pass fuse drawing info to it.
	pUI->DrawFuse(*m_pGfxInfo); //update to draw fuse

}

void Fuse::Operate()
{

}

string* Fuse::Save()
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