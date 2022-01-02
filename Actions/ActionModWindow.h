#pragma once
#include "Action.h"

class ActionModWindow : public Action
{
private:

public:
	ActionModWindow(ApplicationManager* pApp);
	virtual ~ActionModWindow(void);

	//Execute action (code depends on action type)
	virtual void Execute();
	virtual bool Validate();
	virtual void Undo();
	virtual void Redo();


};
