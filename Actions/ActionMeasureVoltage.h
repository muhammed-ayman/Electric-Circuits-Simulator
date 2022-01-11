#include "Action.h"
#include "..\Components\Component.h"
#include "..\Defs.h"

class ActionMeasureVoltage : public Action
{

private:
	Component* CompList[MaxCompCount];

public:
	ActionMeasureVoltage(ApplicationManager* pApp);
	virtual ~ActionMeasureVoltage(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};