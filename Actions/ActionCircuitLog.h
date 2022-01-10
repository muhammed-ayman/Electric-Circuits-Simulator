#pragma once
#include "Action.h"

class ActionCircuitLog : public Action
{
private:

public:
	ActionCircuitLog(ApplicationManager* pApp);
	virtual ~ActionCircuitLog(void);

	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();


};