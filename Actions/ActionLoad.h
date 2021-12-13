#pragma once
#include "Action.h"

class ActionLoad : public Action
{
private:

public:
	
	ActionLoad(ApplicationManager* pApp);
	virtual ~ActionLoad(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};
