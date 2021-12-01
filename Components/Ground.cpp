#include "Ground.h"

Ground::Ground(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{}

void Ground::Draw(UI* pUI)
{
	//Call output class and pass ground drawing info to it.
	pUI->DrawGround(*m_pGfxInfo); //update to draw ground

}

void Ground::Operate()
{

}