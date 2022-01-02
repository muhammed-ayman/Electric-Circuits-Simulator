#pragma once
#include "Component.h"

class Module:public Component
{
public:
	Module(GraphicsInfo *r_GfxInfo); //Constructor that sets item type for the module class
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the Module
	virtual string* Save(); //returns components data to save
};
