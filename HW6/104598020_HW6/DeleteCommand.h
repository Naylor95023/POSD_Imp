#ifndef DELETECOMMAND_H_INCLUDED
#define DELETECOMMAND_H_INCLUDED
#include "Command.h"
#include "Model.h"
#include "Shape.h"
#include "Graphics.h"
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"
#include "Painter.h"
#include <vector>


class DeleteCommand : public Command {
private:
	Model* m_model;
	std::vector<Graphics *> member;
	std::vector<Graphics *> del_member;
public:
	DeleteCommand(Model* m);
	virtual ~DeleteCommand();
	void execute();
	void unexecute();
};

#endif // DELETECOMMAND_H_INCLUDED
