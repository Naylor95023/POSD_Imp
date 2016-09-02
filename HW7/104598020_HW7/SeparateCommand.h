#ifndef SEPARATECOMMAND_H_INCLUDED
#define SEPARATECOMMAND_H_INCLUDED
#include "Command.h"
#include "Model.h"
#include "Shape.h"
#include "Graphics.h"
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"
#include "Painter.h"
#include <vector>
#include <typeinfo>

class SeparateCommand : public Command {
private:
	Model* m_model;
	std::vector<Graphics *> member;
	std::vector<Graphics *> select_member;
	std::vector<Graphics *> child_member;
public:
	SeparateCommand(Model* m);
	virtual ~SeparateCommand();
	void execute();
	void unexecute();
};


#endif // SEPARATECOMMAND_H_INCLUDED
