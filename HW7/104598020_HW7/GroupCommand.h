#ifndef GROUPCOMMAND_H_INCLUDED
#define GROUPCOMMAND_H_INCLUDED
#include "Command.h"
#include "Model.h"
#include "Shape.h"
#include "Graphics.h"
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"
#include "Painter.h"
#include <vector>

class GroupCommand : public Command {
private:
	Model* m_model;
	CompositeGraphics  * cg;
	std::vector<Graphics *> member;
	std::vector<Graphics *> group_member;
public:
	GroupCommand(Model* m);
	virtual ~GroupCommand();
	void execute();
	void unexecute();
};

#endif // GROUPCOMMAND_H_INCLUDED
