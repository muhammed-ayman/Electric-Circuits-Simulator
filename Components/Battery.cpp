#include "Battery.h"

Battery::Battery(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{
	this->itemType = BATTERY;
}

void Battery::Draw(UI* pUI)
{
	//Call output class and pass battery drawing info to it.
	pUI->DrawBattery(*m_pGfxInfo); //update to draw battery

}

void Battery::Operate()
{

}