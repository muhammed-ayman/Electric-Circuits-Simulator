#pragma once
#include "Component.h"

class Resistor:public Component
{
public:
	Resistor();
	Resistor(GraphicsInfo *r_GfxInfo); //Constructor that sets item type for the resistor class
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the resistor
	virtual void Save(ofstream& saveFile, string id); //returns components data to save
	virtual void Load(GraphicsInfo* r_GfxInfo, string label, double value);
};
