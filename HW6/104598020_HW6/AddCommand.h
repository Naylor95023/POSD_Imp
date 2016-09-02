#include "Command.h"
#include "Model.h"
#include "Shape.h"
#include "Graphics.h"
#include "SimpleGraphics.h"

class AddCommand : public Command {
private:
	Model* m_model;
	Graphics  * m_g;
public:
	AddCommand(Model* m, Graphics * m_g);
	virtual ~AddCommand();
	void execute();
	void unexecute();
};
