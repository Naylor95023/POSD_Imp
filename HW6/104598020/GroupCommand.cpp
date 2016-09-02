#include "GroupCommand.h"

GroupCommand::GroupCommand(Model* m) {
	m_model = m;
	cg = new CompositeGraphics();
    for(auto g:m->m_graphics){
        if(g->getPainter()->IsSelected()){
            group_member.push_back(g);
            cg->add(g);
        }else{
            member.push_back(g);
        }
    }
}

GroupCommand::~GroupCommand() {
}

void GroupCommand::execute() {
    m_model->m_graphics.clear();
    for(auto g:member)
        m_model->m_graphics.push_back(g);

    if(cg->compSize()!=0)
        m_model->m_graphics.push_back(cg);
}

void GroupCommand::unexecute() {
    m_model->m_graphics.clear();
    for(auto g:member){
         m_model->m_graphics.push_back(g);
    }
    for(auto g:group_member){
        m_model->m_graphics.push_back(g);
    }
}
