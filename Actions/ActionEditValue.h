#ifndef ACTION_EDIT_VALUE_H
#define ACTION_EDIT_VALUE_H

#include "Action.h"

class ActionEditValue : public Action
{
public:
	ActionEditValue(ApplicationManager* pApp);
	virtual ~ActionEditValue(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif