#include "MoveCommand.h"

MoveCommand::MoveCommand(Graphics * g, int x, int y) {
	m_g = g;
	posX = x;
	posY = y;
}

MoveCommand::~MoveCommand() {
}

void MoveCommand::execute() {
	m_g->moveGraphics(posX, posY);
}

void MoveCommand::unexecute() {
    m_g->moveGraphics(-posX, -posY);
}
