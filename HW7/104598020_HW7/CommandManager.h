#include "Command.h"
#include <stack>

using namespace std;

class CommandManager {
public:
	stack<Command*> m_undoCmds;
	stack<Command*> m_redoCmds;
public:
	CommandManager();
	~CommandManager();
	void execute(Command * c);
	void redo();
	void undo();
	void clearCommand();
};
