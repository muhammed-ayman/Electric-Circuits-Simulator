#pragma once
#pragma once

#include "action.h"
#include "..\Components\Bulb.h"

//Class responsible for adding a new bulb action
class ActionAddBulb : public Action
{
private:
	//Parameters for rectangular area to be occupied by the comp
	int Cx, Cy;	//Center point of the comp
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	Bulb* BulbPointer;
public:
	ActionAddBulb(ApplicationManager* pApp);
	virtual ~ActionAddBulb(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

	virtual void SaveComponentParameters(Bulb* bulbPointer);


};