#ifndef UPLEVELCOMMAND_H_INCLUDED
#define UPLEVELCOMMAND_H_INCLUDED
#include "Command.h"
#include "Model.h"
#include "Shape.h"
#include "Graphics.h"
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"
#include "Painter.h"
#include <vector>
#include <typeinfo>

class UpLevelCommand : public Command {
private:
	CompositeGraphics * root;
	Graphics * selected;
	std::vector<Graphics *> before;
	std::vector<Graphics *> after;
public:
	UpLevelCommand(CompositeGraphics * root);
	virtual ~UpLevelCommand();
	void execute();
	void unexecute();
};


#endif // UPLEVELCOMMAND_H_INCLUDED
