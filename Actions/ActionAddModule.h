#pragma once
#pragma once

#include "action.h"
#include "..\Components\Module.h"

//Class responsible for adding a new battery action
class ActionAddModule : public Action
{
private:
	//Parameters for rectangular area to be occupied by the comp
	int Cx, Cy;	//Center point of the comp
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	Module* ModulePointer;

public:
	ActionAddModule(ApplicationManager* pApp);
	virtual ~ActionAddModule(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

	virtual void SaveComponentParameters(Module* modPointer);

};