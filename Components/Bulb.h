#pragma once
#include "Component.h"

class Bulb:public Component
{
public:
	Bulb();
	Bulb(GraphicsInfo *r_GfxInfo); //Constructor that sets item type for the bulb class
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the bulb
	virtual void Save(ofstream& saveFile, string id); //returns components data to save
	virtual void Load(GraphicsInfo* r_GfxInfo, string label, double value);
};
