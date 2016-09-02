#include "AddCommand.h"


AddCommand::AddCommand(Model* m, Graphics * g) {
	m_model = m;
	m_g = g;
}

AddCommand::~AddCommand() {
}

void AddCommand::execute() {
	m_model->addGraphics(m_g);
}

void AddCommand::unexecute() {
    m_model->deleteLastGraphics();
}
