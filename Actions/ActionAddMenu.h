#ifndef ACTION_ADD_MENU_H
#define ACTION_ADD_MENU_H

#include "Action.h"

class ActionAddMenu : public Action
{
public:
	ActionAddMenu(ApplicationManager* pApp);
	
	virtual ~ActionAddMenu(void);
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};


#endif