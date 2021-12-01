#pragma once
#include "Fuse.h"

class Fuse:public Component
{
public:
	Fuse(GraphicsInfo *r_GfxInfo);
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the fuse

};
