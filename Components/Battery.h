#pragma once
#include "Component.h"

class Battery:public Component
{
public:
	Battery();
	Battery(GraphicsInfo *r_GfxInfo); //Constructor that sets item type for the battery class
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the battery
	virtual void Load(GraphicsInfo* r_GfxInfo, string label, double value);
	virtual void Save(ofstream& saveFile, string id); //returns components data to save
};
