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
#include "ModelSubject.h"

class Presentation : public ModelSubject{
public:
	CommandManager m_cmdManager;
	Model * m_model;
public:
	Presentation(Model* model);
	virtual ~Presentation();
    void SetObserver(GUIObserver * o){this->_observer = o;}
    void NotifyModel(){_observer->UpdateModel();}
    void NotifyUI(){_observer->UpdateUI();}
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
	void clearAll(){
	    m_cmdManager.clearCommand();
	    m_model->m_graphics.clear();
    }
    void cleaCommand(){m_cmdManager.clearCommand();}
	void SelectedChild(CompositeGraphics * cg, int mouseX, int mouseY);
	bool IsHaveChilSelected(CompositeGraphics * cg);
	void DeSelectedChild(CompositeGraphics * cg);
	bool IsModelChanged();
	void getModelDescription();
	std::string HowMuchRootSelected();

	bool redoEnable();
	bool undoEnable();
	bool groupEnable();
	bool separateEnable();
	bool delEnable();
	bool upLevelEnable();
	bool downLevelEnable();

private:
    CompositeGraphics * root;
    std::vector<CompositeGraphics *> levels;
    std::string modelDescription;
};


#endif // PRESENTATION_H_INCLUDED
