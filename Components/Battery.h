#pragma once
#include "Component.h"

class Battery:public Component
{
public:
	Battery(GraphicsInfo *r_GfxInfo); //Constructor that sets item type for the battery class
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the battery
	virtual string* Save(); //returns components data to save
};
