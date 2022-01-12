#pragma once
#include "Component.h"

class Switch:public Component
{
public:
	Switch();
	Switch(GraphicsInfo *r_GfxInfo); //Constructor that sets item type for the switch class
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the switch
	virtual void Load(GraphicsInfo* r_GfxInfo, string label, double value);
	virtual void Save(ofstream& saveFile, string id); //returns components data to save
};
