#pragma once
#include "Component.h"

class Buzzer:public Component
{
public:
	Buzzer(GraphicsInfo *r_GfxInfo); //Constructor that sets item type for the buzzer class
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the buzzer
	virtual string* Save(); //returns components data to save
};
