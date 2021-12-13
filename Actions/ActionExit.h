#pragma once
#include "Action.h"
#include "../Defs.h"
class ActionExit : public Action
{
public:
	ActionExit(ApplicationManager* pApp);

	virtual ~ActionExit(void);
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

