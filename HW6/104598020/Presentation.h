#ifndef PRESENTATION_H_INCLUDED
#define PRESENTATION_H_INCLUDED

#include "CommandManager.h"
#include "AddCommand.h"
#include "GroupCommand.h"
#include "MoveCommand.h"
#include "SeparateCommand.h"
#include "DeleteCommand.h"
#include "UpLevelCommand.h"
#include "DownLevelCommand.h"

#include "Model.h"
#include "Graphics.h"
#include "CompositeGraphics.h"
#include "Shape.h"

class Presentation {
public:
	CommandManager m_cmdManager;
	Model * m_model;
public:
	Presentation(Model* model);
	virtual ~Presentation();
	void addGraphics(Graphics * g);
	void moveGraphics(Graphics * g, int posX, int posY);
	void Group();
	void Separate();
	void Delete();
	void UpLevel();
	void DownLevel();
	bool IsCompChangeLevel(std::string s);
	void redo();
	void undo();
	void SelectedChild(CompositeGraphics * cg, int mouseX, int mouseY);
	bool IsHaveChilSelected(CompositeGraphics * cg);
	void DeSelectedChild(CompositeGraphics * cg);
private:
    CompositeGraphics * root;
    std::vector<CompositeGraphics *> levels;
};


#endif // PRESENTATION_H_INCLUDED
