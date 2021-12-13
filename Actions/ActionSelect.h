#ifndef ACTION_SELECT_H
#define ACTION_SELECT_H

#include "Action.h"
#include "../Defs.h"

class ActionSelect : public Action
{
public:
	ActionSelect(ApplicationManager* pApp);
	
	virtual ~ActionSelect(void);
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};


#endif