#include "Action.h"
#include "..\Components\Component.h"
#include "..\Defs.h"

class ActionMeasureCurrent : public Action
{
private:
	Component* CompList[MaxCompCount];
public:
	ActionMeasureCurrent(ApplicationManager* pApp);
	virtual ~ActionMeasureCurrent(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};