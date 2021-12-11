#pragma once
#include "Action.h"
#include "..\Components\Component.h"

class ActionAddConn : public Action
{
public:
	ActionAddConn(ApplicationManager* pApp);

	virtual ~ActionAddConn(void);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();

};

