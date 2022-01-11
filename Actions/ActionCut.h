#include "Action.h"
#include "../Components/Component.h"
#include "../Components/Connection.h"

class ActionCut : public Action
{
private:
	Component* Comp = nullptr;
	Connection* Conn1 = nullptr;
	Connection* Conn2 = nullptr;

public:
	ActionCut(ApplicationManager* pApp);
	virtual ~ActionCut(void);

	//Execute action (code depends on action type)
	virtual void Execute();


	void SaveActionParameters(Component* Comp, Connection* Conn1, Connection* Conn2);

	virtual void Undo();
	virtual void Redo();


};