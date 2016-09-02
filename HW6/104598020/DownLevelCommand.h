#ifndef DOWNLEVELCOMMAND_H_INCLUDED
#define DOWNLEVELCOMMAND_H_INCLUDED
#include "Command.h"
#include "Model.h"
#include "Shape.h"
#include "Graphics.h"
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"
#include "Painter.h"
#include <vector>
#include <typeinfo>

class DownLevelCommand : public Command {
private:
	CompositeGraphics * root;
	Graphics * selected;
	std::vector<Graphics *> before;
	std::vector<Graphics *> after;
public:
	DownLevelCommand(CompositeGraphics * root);;
	virtual ~DownLevelCommand();
	void execute();
	void unexecute();
};


#endif // DOWNLEVELCOMMAND_H_INCLUDED
