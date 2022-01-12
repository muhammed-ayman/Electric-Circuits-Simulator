#include "Action.h"

class ActionAddDefault : public Action
{

public:
	ActionAddDefault(ApplicationManager* pApp);
	virtual ~ActionAddDefault(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};