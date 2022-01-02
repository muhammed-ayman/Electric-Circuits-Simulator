#pragma once
#include "Component.h"

class Switch:public Component
{
public:
	Switch(GraphicsInfo *r_GfxInfo); //Constructor that sets item type for the switch class
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the switch
	virtual string* Save(); //returns components data to save
};
