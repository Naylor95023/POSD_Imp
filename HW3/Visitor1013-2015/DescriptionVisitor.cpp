#include "DescriptionVisitor.h"

void DescriptionVisitor::visitSimpleGraphics(SimpleGraphics *s) {
    std::string sp = "";
    //print space
    for(int i = 0; i < level * 2; i++) sp += " ";
    d += sp + s->getShape()->describe()+'\n';

    //1.Every time last child's value -1;
    if(!childs.empty() && childs[childs.size() - 1] != 0)childs[childs.size() - 1] -= 1;
    //2.If last one become 0, mean this level been over,so level-1 and pop_back
    if(!childs.empty() && childs[childs.size() - 1] == 0){
            childs.pop_back();
            level--;
    }
}
void DescriptionVisitor::visitCompositeGraphics(CompositeGraphics *c) {
    std::string sp = "";
    //Anytime go in child's value have to -1,even is comp type
    if(!childs.empty() && childs[childs.size() - 1] != 0)childs[childs.size() - 1] -= 1;
    //Here don't have to check if last child value,
    //because when come to this method,the Comp be empty is impossible

    //print space
    for(int i = 0; i < level * 2; i++) sp += " ";
    d += sp + "Comp " + c->getBoundingBox().describe() + '\n';

    //When push_back into child, meaning go to next level,so level++
    if(c->getSize() > 0)childs.push_back(c->getSize());
    level++;


}

std::string DescriptionVisitor::getDescription() {
    return d;
}
