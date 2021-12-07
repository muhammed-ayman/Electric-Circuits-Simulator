#include "Fuse.h"

Fuse::Fuse(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{
	this->itemType = FUSE;
}

void Fuse::Draw(UI* pUI)
{
	//Call output class and pass fuse drawing info to it.
	pUI->DrawFuse(*m_pGfxInfo); //update to draw fuse

}

void Fuse::Operate()
{

}