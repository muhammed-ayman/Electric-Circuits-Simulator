#pragma once
#pragma once

#include "action.h"
#include "..\Components\Fuse.h"

//Class responsible for adding a new fuse action
class ActionAddFuse : public Action
{
private:
	//Parameters for rectangular area to be occupied by the comp
	int Cx, Cy;	//Center point of the comp
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	Fuse* FusePointer;
public:
	ActionAddFuse(ApplicationManager* pApp);
	virtual ~ActionAddFuse(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

	virtual void SaveComponentParameters(Fuse* bulbPointer);


};