#include "Presentation.h"
#include <cstdio>
Presentation::Presentation(Model* m) {
	m_model = m;
}

Presentation::~Presentation() {
}

void Presentation::addGraphics(Graphics  * g){
	m_cmdManager.execute(new AddCommand(m_model, g));
}

void Presentation::moveGraphics(Graphics * g, int posX, int posY){
	m_cmdManager.execute(new MoveCommand(g, posX, posY));

}

void Presentation::Group(){
	m_cmdManager.execute(new GroupCommand(m_model));
}

void Presentation::Delete(){
    m_cmdManager.execute(new DeleteCommand(m_model));
}

void Presentation::Separate(){
    m_cmdManager.execute(new SeparateCommand(m_model));
}

void Presentation::UpLevel(){
    if(IsCompChangeLevel("up"))
        m_cmdManager.execute(new UpLevelCommand(root));
}

void Presentation::DownLevel(){
    if(IsCompChangeLevel("down"))
        m_cmdManager.execute(new DownLevelCommand(root));
}

void Presentation::redo() {
	m_cmdManager.redo();
}

void Presentation::undo() {
	m_cmdManager.undo();
}

void Presentation::SelectedChild(CompositeGraphics * cg, int mouseX, int mouseY) {
    levels.push_back(cg);
	for(auto g:cg->g_obj){
        if(mouseX > g->getBoundingBox().llx() && mouseX < g->getBoundingBox().urx() &&
           mouseY > g->getBoundingBox().lly() && mouseY < g->getBoundingBox().ury()){
            g->getPainter()->setSelected();
            if(typeid((*g)) == typeid(CompositeGraphics)){
                CompositeGraphics * child_cg = reinterpret_cast<CompositeGraphics *>(g);
                SelectedChild(child_cg, mouseX, mouseY);
            }
        }
    }
}

void Presentation::DeSelectedChild(CompositeGraphics * cg) {
	for(auto g:cg->g_obj){
        g->getPainter()->setNotSelected();
        if(typeid((*g)) == typeid(CompositeGraphics)){
            CompositeGraphics * child_cg = reinterpret_cast<CompositeGraphics *>(g);
            DeSelectedChild(child_cg);
        }
    }
    levels.clear();
}

bool Presentation::IsHaveChilSelected(CompositeGraphics * cg){
    for(auto g:cg->g_obj)
        if(g->getPainter()->IsSelected())return true;
    return false;
}

bool Presentation::IsCompChangeLevel(std::string s) {
    if(!IsHaveChilSelected(levels.back()) && levels.size()>1)levels.pop_back();
    root = levels.back();
    //find selected
    int level = 0;
    int obj_size = root->g_obj.size();
    for(auto child_g:root->g_obj){
        level++;
        if(child_g->getPainter()->IsSelected()){
            if(obj_size == 1)return false;
            if(level == 1 && s == "up")return false;
            if(level == obj_size && s == "down")return false;
            return true;
        }
    }
    return false;
}
