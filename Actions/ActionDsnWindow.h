#pragma once
#include "Action.h"

class ActionDsnWindow : public Action
{
private:

public:
	ActionDsnWindow(ApplicationManager* pApp);
	virtual ~ActionDsnWindow(void);

	bool Validate();

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};
