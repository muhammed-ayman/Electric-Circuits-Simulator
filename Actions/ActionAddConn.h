#pragma once
#include "Action.h"
#include "..\Components\Component.h"
#include "..\Defs.h"

class ActionAddConn : public Action
{
private:
	Component* CompList[200];
	ConnectionInfo* cInfo = new ConnectionInfo;
	GraphicsInfo* conn_graph_info = new GraphicsInfo(2);

public:
	ActionAddConn(ApplicationManager* pApp);
	void ProcessConnection(ConnectionInfo* cInfo);
	virtual ~ActionAddConn(void);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();

};
