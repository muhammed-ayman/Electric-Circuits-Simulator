#ifndef ACTION_ADD_MENU_H
#define ACTION_ADD_MENU_H

#include "../ApplicationManager.h"
#include "../Components/Component.h"

class ActionAddMenu {

protected:
	ApplicationManager* pManager;

public:

	ActionAddMenu(ApplicationManager* pApp) { pManager = pApp; }

	void DrawComponentMenu(Component* Comp); // Drawing the component menu. Takes pointer of type Component as a parameter.
	
	~ActionAddMenu();

};

#endif