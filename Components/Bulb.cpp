#include "Bulb.h"

Bulb::Bulb(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{}

void Bulb::Draw(UI* pUI)
{
	//Call output class and pass bulb drawing info to it.
	pUI->DrawBulb(*m_pGfxInfo); //update to draw bulb

}

void Bulb::Operate()
{

}