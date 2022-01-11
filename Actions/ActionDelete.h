#pragma once
#include "Action.h"
#include "../Components/Component.h"
#include "../Components/Connection.h"
#include <stack>

class ActionDelete : public Action
{
private:
	stack<Component*> targetComponentsRedo;
	stack<Component*> targetComponentsUndo;
	int deletedComponentRedoCounter;
	int deletedComponentUndoCounter;

	stack<Connection*> targetConnectionsRedo;
	stack<Connection*> targetConnectionsUndo;
	int deletedConnectionsRedoCounter;
	int deletedConnectionsUndoCounter;

	public:
		ActionDelete(ApplicationManager* pApp);

		//Execute action (code depends on action type)
		virtual void Execute();

		// Saving the Action Parameters
		void SaveComponentParameters(Component* Comp);
		void SaveConnectionParameters(Connection* Conn);

		virtual void Undo();
		virtual void Redo();

		~ActionDelete();

};

