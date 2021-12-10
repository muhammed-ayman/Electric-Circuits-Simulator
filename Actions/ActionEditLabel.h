#ifndef ACTION_EDIT_LABEL_H
#define ACTION_EDIT_LABEL_H

#include "Action.h"

class ActionEditLabel : public Action
{
public:
	ActionEditLabel(ApplicationManager* pApp);
	virtual ~ActionEditLabel(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

	
};

#endif