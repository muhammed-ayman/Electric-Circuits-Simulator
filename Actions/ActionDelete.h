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

		//Execute action (code depends on action type)
		virtual void Execute();

		void SaveComponentParameters(Component* Comp); // Saving the Action Parameters

		virtual void Undo();
		virtual void Redo();

		~ActionDelete();

};

