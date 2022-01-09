#pragma once

#include "Action.h"

// Class responsible for Redoing an Action
class ActionRedo : public Action
{

public:
	ActionRedo(ApplicationManager* pApp);
	virtual ~ActionRedo(void);

	// Execute The Action
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};