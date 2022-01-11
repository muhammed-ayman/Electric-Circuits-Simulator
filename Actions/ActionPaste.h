#include "Action.h"
#include "../Components/Component.h"
#include "../Components/Connection.h"

class ActionPaste : public Action
{
private:
	//Parameters for rectangular area to be occupied by the comp
	int Cx, Cy;	//Center point of the comp
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	Component* Comp = nullptr;
	Connection* Conn1 = nullptr;
	Connection* Conn2 = nullptr;

public:
	ActionPaste(ApplicationManager* pApp);
	virtual ~ActionPaste(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	void SaveActionParameters(Component* Comp, Connection* Conn1, Connection* Conn2);

	virtual void Undo();
	virtual void Redo();
};