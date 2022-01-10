#include "Action.h"

class ActionMeasureVoltage : public Action
{


public:
	ActionMeasureVoltage(ApplicationManager* pApp);
	virtual ~ActionMeasureVoltage(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};