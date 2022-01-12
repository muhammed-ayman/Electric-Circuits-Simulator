#pragma once
#include "Component.h"

class Fuse:public Component
{
public:
	Fuse();
	Fuse(GraphicsInfo *r_GfxInfo); //Constructor that sets item type for the fuse class
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the fuse
	virtual void Load(GraphicsInfo* r_GfxInfo, string label, double value);
	virtual void Save(ofstream& saveFile, string id); //returns components data to save
};
