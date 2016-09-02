#include "UpLevelCommand.h"

UpLevelCommand::UpLevelCommand(CompositeGraphics * root) {
    this->root = root;
    int index = 0;
    for(auto g:root->g_obj){
        if(g->getPainter()->IsSelected()){
            selected = g;
            break;
        }
        index++;
    }
    for(int i = 0; i < index; i++)
        before.push_back(root->g_obj[i]);
    for(int i = index + 1; i < root->g_obj.size(); i++)
        after.push_back(root->g_obj[i]);
}

UpLevelCommand::~UpLevelCommand() {
}

void UpLevelCommand::execute() {
    root->g_obj.clear();

    for(int i=0; i < before.size()-1; i++)
        root->add(before[i]);

    root->add(selected);
    root->add(before[before.size()-1]);

    for(int i=0; i < after.size(); i++)
        root->add(after[i]);
}

void UpLevelCommand::unexecute() {
    root->g_obj.clear();

    for(int i=0; i < before.size(); i++)
        root->add(before[i]);

    root->add(selected);

    for(int i=0; i < after.size(); i++)
        root->add(after[i]);
}
