#ifndef ACTION_ADD_MENU_H
#define ACTION_ADD_MENU_H

#include "../ApplicationManager.h"

class ActionAddMenu {

protected:
	ApplicationManager* pManager;

public:

	ActionAddMenu(ApplicationManager* pApp) { pManager = pApp; }

	void DrawComponentMenu();
	
	~ActionAddMenu();

};

#endif