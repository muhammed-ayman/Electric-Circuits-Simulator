#pragma once
#include "Action.h"
class ActionMove :
    public Action
{
public:
	ActionMove(ApplicationManager* pApp);
	virtual ~ActionMove(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};