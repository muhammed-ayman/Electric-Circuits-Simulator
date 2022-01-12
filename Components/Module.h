#pragma once
#include "Component.h"

class Module:public Component
{
private:
	int CompCount = 0;
	int ConnCount = 0;

	bool writeable = true;

	Component* CompList[MaxCompCount];
	Connection* ConnList[MaxConnCount];

public:
	Module();
	Module(GraphicsInfo *r_GfxInfo); //Constructor that sets item type for the module class
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the Module
	virtual void Save(ofstream& saveFile, string id); //returns components data to save
	virtual void Load(GraphicsInfo* r_GfxInfo, string label, double value);

	void SetCompList(Component* CompListNew[]);
	void SetConnList(Connection* CompListNew[]);
	void GetCompList(Component* CompListNew[]);
	void GetConnList(Connection* CompListNew[]);
	void SetCompCount(int CompCount);
	void SetConnCount(int ConnCount);
	int GetCompCount();
	int GetConnCount();
	void setWriteMode(bool mode);
	bool getWriteMode();
};
