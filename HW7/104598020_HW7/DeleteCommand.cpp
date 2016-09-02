#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(Model* m) {
	m_model = m;
    for(auto g:m->m_graphics){
        if(g->getPainter()->IsSelected()){
            del_member.push_back(g);
        }else{
            member.push_back(g);
        }
    }
}

DeleteCommand::~DeleteCommand() {
}

void DeleteCommand::execute() {
    m_model->m_graphics.clear();
    for(auto g:member)
        m_model->m_graphics.push_back(g);
}

void DeleteCommand::unexecute() {
    m_model->m_graphics.clear();
    for(auto g:member){
         m_model->m_graphics.push_back(g);
    }
    for(auto g:del_member){
        m_model->m_graphics.push_back(g);
    }
}
