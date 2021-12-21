
#pragma once
#include "Action.h"

class ActionSimWindow : public Action
{
private:

public:
	ActionSimWindow(ApplicationManager* pApp);
	virtual ~ActionSimWindow(void);

	//Execute action (code depends on action type)
	virtual void Execute();
	virtual bool Validate();
	virtual void Undo();
	virtual void Redo();


};
