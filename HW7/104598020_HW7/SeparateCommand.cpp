#include "SeparateCommand.h"

SeparateCommand::SeparateCommand(Model* m) {
	m_model = m;
    for(auto g:m->m_graphics){
        if(g->getPainter()->IsSelected()){
            select_member.push_back(g);
            if(typeid((*g)) == typeid(CompositeGraphics)){
                CompositeGraphics * cg = reinterpret_cast<CompositeGraphics *>(g);
                for(auto cg_child:cg->g_obj)
                    child_member.push_back(cg_child);
            }else {
                child_member.push_back(g);
            }
        }else{
            member.push_back(g);
        }
    }
}

SeparateCommand::~SeparateCommand() {
}

void SeparateCommand::execute() {
    m_model->m_graphics.clear();
    for(auto g:member)
        m_model->m_graphics.push_back(g);
    for(auto g:child_member){
        m_model->m_graphics.push_back(g);
    }
}

void SeparateCommand::unexecute() {
    m_model->m_graphics.clear();
    for(auto g:member){
         m_model->m_graphics.push_back(g);
    }
    for(auto g:select_member){
        m_model->m_graphics.push_back(g);
    }
}
