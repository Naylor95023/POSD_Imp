#ifndef MOVECOMMAND_H_INCLUDED
#define MOVECOMMAND_H_INCLUDED
#include "Command.h"
#include "Model.h"
#include "Shape.h"
#include "Graphics.h"
#include "SimpleGraphics.h"

class MoveCommand : public Command {
private:
	Graphics  * m_g;
	int posX;
	int posY;
public:
	MoveCommand(Graphics * m_g, int x, int y);
	virtual ~MoveCommand();
	void execute();
	void unexecute();
};



#endif // MOVECOMMAND_H_INCLUDED
