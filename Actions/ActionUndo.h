#pragma once

#include "Action.h"

// Class responsible for Redoing an Action
class ActionUndo : public Action
{

public:
	ActionUndo(ApplicationManager* pApp);
	virtual ~ActionUndo(void);

	// Execute The Action
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};