#include "Buzzer.h"

Buzzer::Buzzer(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{}

void Buzzer::Draw(UI* pUI)
{
	//Call output class and pass buzzer drawing info to it.
	pUI->DrawBuzzer(*m_pGfxInfo); //update to draw buzzer

}

void Buzzer::Operate()
{

}