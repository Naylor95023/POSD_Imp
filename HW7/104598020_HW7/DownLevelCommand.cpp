#include "DownLevelCommand.h"

DownLevelCommand::DownLevelCommand(CompositeGraphics * root) {
    this->root = root;
    int index = 0;
    for(auto g:root->g_obj){
        if(g->getPainter()->IsSelected()){
            selected = g;
            break;
        }
        index++;
    }
    cout << "index" << index << endl;
    for(int i = 0; i < index; i++)
        before.push_back(root->g_obj[i]);
    for(int i = index + 1; i < root->g_obj.size(); i++)
        after.push_back(root->g_obj[i]);
}

DownLevelCommand::~DownLevelCommand() {
}

void DownLevelCommand::execute() {
    root->g_obj.clear();

    for(int i=0; i < before.size(); i++)
        root->add(before[i]);
    cout << before.size() << endl;
    cout << after.size() << endl;
    if(after.size() > 0){
        root->add(after[0]);

    }
    root->add(selected);

    for(int i=1; i < after.size(); i++)
        root->add(after[i]);
}

void DownLevelCommand::unexecute() {
    root->g_obj.clear();

    for(int i=0; i < before.size(); i++)
        root->add(before[i]);

    root->add(selected);

    for(int i=0; i < after.size(); i++)
        root->add(after[i]);
}
