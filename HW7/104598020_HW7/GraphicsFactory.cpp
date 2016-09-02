#include "GraphicsFactory.h"

using namespace std;

void GraphicsFactory::buildGraphicsFromFile(const char * fileName, Presentation * m_p){
    Graphics * lineGraphics;
    string fileString,line;
    std::stringstream ss;
    int currentLevel, level = 0;

    //get File to String
    fileString = fileContentsAsString(fileName);
    ss << fileString;

    //build Graphics
    while(getline(ss,line)){
        currentLevel = level;
        lineGraphics = extractGraphicsFromOneLine(line,level);

        //when turn back, do compose()
        if(currentLevel > level) compose();
        _graphicsStack.push(make_pair(lineGraphics, level));

        //one graphics is end
        if(level == 0 && _graphicsStack.size() == 2){
            Graphics * temp = _graphicsStack.top().first;
            _graphicsStack.pop();
            m_p -> addGraphics(_graphicsStack.top().first);
            _graphicsStack.pop();
            if(typeid((*temp)) == typeid(CompositeGraphics))
                _graphicsStack.push(make_pair(temp, 0));
            else m_p-> addGraphics(temp);
        }
    }


    if(_graphicsStack.size()>1){
        compose();
        lineGraphics = _graphicsStack.top().first;
        _graphicsStack.pop();
        m_p -> addGraphics(lineGraphics);
    }
    if(_graphicsStack.size() == 1){
        cout << _graphicsStack.size() << endl;
        m_p -> addGraphics(lineGraphics);
    }
}


string GraphicsFactory::fileContentsAsString(const char * fileName){
    fstream fin;
    string s,line;
    fin.open(fileName,ios::in);
    if(!fin)throw string("File not exist!!!");
    else {
        while(getline(fin,line)){
            s += line + '\n';
        }
    }
    fin.close();
    return s;
}


Graphics * GraphicsFactory::extractGraphicsFromOneLine(std::string & contents, int & level){
    //which level now
    int spaceCount = 0;
    for(int i = 0; i < contents.size(); i++){
        if(contents[i] == ' ') spaceCount++;
    }
    level = spaceCount / 2;
    //comp
    int index = contents.find("Comp");
    if(index != string::npos){
            return new CompositeGraphics();
    }
    //cir
    index = contents.find("C");
    if(index != string::npos){
            int x, y,r;
            sscanf(contents.c_str(), " C(%d,%d,%d)", &x, &y, &r);
            return new SimpleGraphics(new Circle(x, y, r));
    }
    //squ
    index = contents.find("S");
    if(index != string::npos){
            int x,y,l;
            sscanf(contents.c_str(), " S(%d,%d,%d)", &x, &y, &l);
            return new SimpleGraphics(new Square(x, y, l));
    }
    //rec
    index = contents.find("R");
    if(index != string::npos){
            int x,y,l,h;
            sscanf(contents.c_str(), " R(%d,%d,%d,%d)", &x, &y, &l, &h);
            return new SimpleGraphics(new Rectangle(x, y, l, h));
    }

}


void GraphicsFactory::compose (){
    Graphics * temp;
    stack<Graphics *> childs;
    int currentLevel = 0;
    currentLevel = _graphicsStack.top().second;
    //get childs and pop
    while(currentLevel == _graphicsStack.top().second){
        childs.push(_graphicsStack.top().first);
        _graphicsStack.pop();
    }
    //do compose, then push back
    temp = _graphicsStack.top().first;
    _graphicsStack.pop();
    while(!childs.empty()){
        temp ->add(childs.top());
        childs.pop();
    }
    _graphicsStack.push(make_pair(temp, currentLevel - 1));
}

