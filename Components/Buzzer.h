#pragma once
#include "Component.h"

class Buzzer:public Component
{
public:
	Buzzer();
	Buzzer(GraphicsInfo *r_GfxInfo); //Constructor that sets item type for the buzzer class
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the buzzer
	virtual void Load(GraphicsInfo* r_GfxInfo, string label, double value);
	virtual void Save(ofstream& saveFile, string id); //returns components data to save
};
