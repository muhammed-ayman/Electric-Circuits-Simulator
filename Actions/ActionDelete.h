#pragma once
#include "Action.h"
#include "../Components/Component.h"
#include <stack>

class ActionDelete : public Action
{
private:
	stack<Component*> targetComponentsRedo;
	stack<Component*> targetComponentsUndo;
	int deletedComponentRedoCounter;
	int deletedComponentUndoCounter;

	public:
		ActionDelete(ApplicationManager* pApp);
		virtual ~ActionDelete(void);

		//Execute action (code depends on action type)
		virtual void Execute();

		virtual void Undo();
		virtual void Redo();

		void SaveComponentParameters(Component* Comp);

};

