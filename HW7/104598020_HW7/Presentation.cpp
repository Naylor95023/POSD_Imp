#include "Presentation.h"
#include <cstdio>
Presentation::Presentation(Model* m) {
	m_model = m;
	modelDescription = "File: ";

}

Presentation::~Presentation() {
}

void Presentation::addGraphics(Graphics  * g){
	m_cmdManager.execute(new AddCommand(m_model, g));
	NotifyModel();
	NotifyUI();
}

void Presentation::moveGraphics(Graphics * g, int posX, int posY){
	m_cmdManager.execute(new MoveCommand(g, posX, posY));
}

void Presentation::Group(){
	m_cmdManager.execute(new GroupCommand(m_model));
	NotifyModel();
	NotifyUI();
}

void Presentation::Delete(){
    m_cmdManager.execute(new DeleteCommand(m_model));
    NotifyModel();
	NotifyUI();
}

void Presentation::Separate(){
    m_cmdManager.execute(new SeparateCommand(m_model));
    NotifyModel();
	NotifyUI();
	levels.clear();
}

void Presentation::UpLevel(){
    if(IsCompChangeLevel("up")){
        m_cmdManager.execute(new UpLevelCommand(root));
        NotifyModel();
        NotifyUI();
    }

}

void Presentation::DownLevel(){
    if(IsCompChangeLevel("down")){
        m_cmdManager.execute(new DownLevelCommand(root));
        NotifyModel();
        NotifyUI();
    }

}

void Presentation::redo() {
	m_cmdManager.redo();
	NotifyModel();
	NotifyUI();
}

void Presentation::undo() {
	m_cmdManager.undo();
	NotifyModel();
	NotifyUI();
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
    //no selected
    if(levels.empty())return false;
    //one root selected ,then child's child...
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

bool Presentation::IsModelChanged(){
    if(modelDescription == m_model->toString())return false;
    else return true;
}

void Presentation::getModelDescription(){
    modelDescription = m_model->toString();
}

std::string Presentation::HowMuchRootSelected(){
    int roots = 0;
    Graphics * temp;
    std::string COMPOSITE_ROOT = "COMPOSITE_ROOT";
    std::string SIMPLE_ROOT = "SIMPLE_ROOT";
    std::string MANY_ROOTS = "MANY_ROOTS";
    for (auto g:m_model->m_graphics){
        if (g->getPainter()->IsSelected()&&(typeid(*g)==typeid(SimpleGraphics))){
            temp = g;
            roots++;
        }
        if (g->getPainter()->IsSelected()&&(typeid(*g)==typeid(CompositeGraphics))){
            temp = g;
            CompositeGraphics * cg = reinterpret_cast<CompositeGraphics *>(g);
            if(IsHaveChilSelected(cg))return "x";
            else roots++;
        }
    }

    if(roots == 1 &&(typeid(*temp)==typeid(SimpleGraphics)))return SIMPLE_ROOT;
    if(roots == 1 &&(typeid(*temp)==typeid(CompositeGraphics)))return COMPOSITE_ROOT;
    if(roots > 1)return MANY_ROOTS;
    return "x";
}

bool Presentation::redoEnable(){
    if(m_cmdManager.m_redoCmds.empty())return false;
    else return true;
}

bool Presentation::undoEnable(){
    if(m_cmdManager.m_undoCmds.empty())return false;
    else return true;
}

bool Presentation::groupEnable(){
     if(HowMuchRootSelected() == "MANY_ROOTS")
        return true;
     else return false;
}

bool Presentation::separateEnable(){
     if(HowMuchRootSelected() == "COMPOSITE_ROOT")
        return true;
     else return false;
}

bool Presentation::delEnable(){
     if(HowMuchRootSelected() == "SIMPLE_ROOT"||HowMuchRootSelected() == "COMPOSITE_ROOT")
        return true;
     else return false;
}

bool Presentation::upLevelEnable(){
    if(IsCompChangeLevel("up"))return true;
    else return false;
}

bool Presentation::downLevelEnable(){
    if(IsCompChangeLevel("down"))return true;
    else return false;
}
