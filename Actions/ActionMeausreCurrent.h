#include "Action.h"

class ActionMeasureCurrent : public Action
{


public:
	ActionMeasureCurrent(ApplicationManager* pApp);
	virtual ~ActionMeasureCurrent(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};