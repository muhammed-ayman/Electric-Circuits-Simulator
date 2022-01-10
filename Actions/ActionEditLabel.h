#ifndef ACTION_EDIT_LABEL_H
#define ACTION_EDIT_LABEL_H

#include "Action.h"
#include "../ApplicationManager.h"

class ActionEditLabel : public Action
{
private:
	int targetComponent = -1;
	int targetConnection = -1;
	string previousLabel;

public:
	ActionEditLabel(ApplicationManager* pApp);
	virtual ~ActionEditLabel(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

	virtual void SaveComponentParameters(int SelectedItemId, string preLabel);
	virtual void SaveConnectionParameters(int SelectedItemId, string preLabel);

	
};

#endif