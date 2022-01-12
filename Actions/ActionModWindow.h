#pragma once
#include "Action.h"
#include "../Components/Component.h"

class ActionModWindow : public Action
{
private:
	Component* Mod_CompList[MaxCompCount];	//List of all Components (Array of pointers)
	Connection* Mod_ConnList[MaxConnCount]; // List of all Connections (Array of pointers)

public:
	ActionModWindow(ApplicationManager* pApp);
	virtual ~ActionModWindow(void);

	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();


};
